/*
 * firmware-header-parser.c - GPU firmware binary header parser
 *
 * Parses a binary firmware image whose headers are stored in little-endian
 * byte order, handling endianness transparently on both LE and BE hosts.
 *
 * Firmware binary layout:
 *
 *   [ common_firmware_header   ]  -- magic, version, total size, checksum
 *   [ <type-specific header>   ]  -- gfx / sdma / rlc / smc ...
 *   [ firmware payload         ]
 *
 * Inspired by AMD AMDGPU firmware header conventions (amdgpu_ucode.h).
 */

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

/* ---------- endianness helpers ------------------------------- */

/*
 * The firmware blob is always little-endian.  On a little-endian host
 * these are no-ops; on a big-endian host they byte-swap.
 */
static inline uint16_t le16_to_cpu(uint16_t v)
{
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return (uint16_t)((v >> 8) | (v << 8));
#else
	return v;
#endif
}

static inline uint32_t le32_to_cpu(uint32_t v)
{
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return ((v & 0x000000FFu) << 24) |
	       ((v & 0x0000FF00u) <<  8) |
	       ((v & 0x00FF0000u) >>  8) |
	       ((v & 0xFF000000u) >> 24);
#else
	return v;
#endif
}

static inline uint32_t cpu_to_le32(uint32_t v)
{
	return le32_to_cpu(v);	/* symmetric */
}

/* ---------- firmware magic ----------------------------------- */
#define AMDGPU_FW_MAGIC		0x414D4447u	/* "AMDG" */

/* ---------- firmware type IDs -------------------------------- */
enum fw_type {
	FW_TYPE_GFX_ME		= 0x01,
	FW_TYPE_GFX_PFP		= 0x02,
	FW_TYPE_GFX_CE		= 0x03,
	FW_TYPE_GFX_MEC		= 0x04,
	FW_TYPE_SDMA		= 0x10,
	FW_TYPE_RLC		= 0x20,
	FW_TYPE_SMC		= 0x30,
	FW_TYPE_MAX,
};

static const char *fw_type_name(uint8_t type)
{
	switch (type) {
	case FW_TYPE_GFX_ME:	return "GFX_ME";
	case FW_TYPE_GFX_PFP:	return "GFX_PFP";
	case FW_TYPE_GFX_CE:	return "GFX_CE";
	case FW_TYPE_GFX_MEC:	return "GFX_MEC";
	case FW_TYPE_SDMA:	return "SDMA";
	case FW_TYPE_RLC:	return "RLC";
	case FW_TYPE_SMC:	return "SMC";
	default:		return "UNKNOWN";
	}
}

/* ---------- on-disk structures (all fields little-endian) ---- */

/*
 * Every firmware image begins with this common header.
 * Fields are __le32 / __le16 to document on-disk byte order.
 */
struct common_firmware_header {
	uint32_t	size_bytes;	/* total image size including headers */
	uint32_t	header_size;	/* size of this common header */
	uint16_t	header_version_major;
	uint16_t	header_version_minor;
	uint32_t	ip_version_major;
	uint32_t	ip_version_minor;
	uint32_t	ucode_version;
	uint32_t	ucode_size_bytes;	/* payload size */
	uint32_t	ucode_array_offset;	/* offset from start of header */
	uint32_t	crc32;			/* CRC32 of payload */
	uint32_t	magic;			/* AMDGPU_FW_MAGIC */
	uint8_t		fw_type;		/* enum fw_type */
	uint8_t		reserved[3];
} __attribute__((packed));

/* GFX (ME / PFP / CE / MEC) extended header */
struct gfx_firmware_header {
	struct common_firmware_header	common;
	uint32_t			ucode_feature_version;
	uint32_t			jt_offset;	/* jump table offset */
	uint32_t			jt_size;
} __attribute__((packed));

/* SDMA extended header */
struct sdma_firmware_header {
	struct common_firmware_header	common;
	uint32_t			ucode_feature_version;
	uint32_t			ucode2_offset;	/* offset of 2nd ucode */
	uint32_t			ucode2_size;
} __attribute__((packed));

/* RLC extended header */
struct rlc_firmware_header {
	struct common_firmware_header	common;
	uint32_t			ucode_feature_version;
	uint32_t			save_and_restore_offset;
	uint32_t			clear_state_descriptor_offset;
	uint32_t			avail_scratch_ram_locations;
	uint32_t			master_pkt_description_offset;
} __attribute__((packed));

/* SMC extended header */
struct smc_firmware_header {
	struct common_firmware_header	common;
	uint32_t			ucode_start_addr;
} __attribute__((packed));

/* ---------- parsed (host-endian) representation -------------- */
struct fw_info {
	uint32_t	total_size;
	uint32_t	header_size;
	uint16_t	ver_major;
	uint16_t	ver_minor;
	uint32_t	ip_ver_major;
	uint32_t	ip_ver_minor;
	uint32_t	ucode_version;
	uint32_t	ucode_size;
	uint32_t	ucode_offset;
	uint32_t	crc32;
	uint8_t		fw_type;

	/* type-specific */
	union {
		struct {
			uint32_t feature_version;
			uint32_t jt_offset;
			uint32_t jt_size;
		} gfx;
		struct {
			uint32_t feature_version;
			uint32_t ucode2_offset;
			uint32_t ucode2_size;
		} sdma;
		struct {
			uint32_t feature_version;
			uint32_t save_restore_offset;
			uint32_t clear_state_offset;
			uint32_t scratch_locations;
		} rlc;
		struct {
			uint32_t ucode_start_addr;
		} smc;
	};
};

/* ---------- CRC-32 (IEEE 802.3 polynomial) ------------------- */
static uint32_t crc32_compute(const uint8_t *data, size_t len)
{
	static uint32_t table[256];
	static int table_ready;
	uint32_t crc;
	size_t i;

	if (!table_ready) {
		uint32_t c;
		unsigned int k, j;

		for (k = 0; k < 256; k++) {
			c = k;
			for (j = 0; j < 8; j++)
				c = (c & 1) ? (0xEDB88320u ^ (c >> 1)) : (c >> 1);
			table[k] = c;
		}
		table_ready = 1;
	}

	crc = 0xFFFFFFFFu;
	for (i = 0; i < len; i++)
		crc = table[(crc ^ data[i]) & 0xFF] ^ (crc >> 8);
	return crc ^ 0xFFFFFFFFu;
}

/* ---------- parser ------------------------------------------- */

static int parse_common_header(const uint8_t *buf, size_t buf_len,
				struct fw_info *info)
{
	const struct common_firmware_header *hdr;
	uint32_t magic, total_size;

	if (buf_len < sizeof(*hdr)) {
		fprintf(stderr, "firmware too small: %zu bytes\n", buf_len);
		return -EINVAL;
	}

	hdr = (const struct common_firmware_header *)buf;

	/* validate magic */
	magic = le32_to_cpu(hdr->magic);
	if (magic != AMDGPU_FW_MAGIC) {
		fprintf(stderr, "bad magic: 0x%08X (expected 0x%08X)\n",
			magic, AMDGPU_FW_MAGIC);
		return -EINVAL;
	}

	total_size = le32_to_cpu(hdr->size_bytes);
	if (total_size > buf_len) {
		fprintf(stderr, "header says %u bytes but buffer is %zu\n",
			total_size, buf_len);
		return -EINVAL;
	}

	info->total_size   = total_size;
	info->header_size  = le32_to_cpu(hdr->header_size);
	info->ver_major    = le16_to_cpu(hdr->header_version_major);
	info->ver_minor    = le16_to_cpu(hdr->header_version_minor);
	info->ip_ver_major = le32_to_cpu(hdr->ip_version_major);
	info->ip_ver_minor = le32_to_cpu(hdr->ip_version_minor);
	info->ucode_version = le32_to_cpu(hdr->ucode_version);
	info->ucode_size   = le32_to_cpu(hdr->ucode_size_bytes);
	info->ucode_offset = le32_to_cpu(hdr->ucode_array_offset);
	info->crc32        = le32_to_cpu(hdr->crc32);
	info->fw_type      = hdr->fw_type;

	/* validate ucode bounds */
	if ((uint64_t)info->ucode_offset + info->ucode_size > total_size) {
		fprintf(stderr, "ucode region [%u, %u) exceeds image size %u\n",
			info->ucode_offset,
			info->ucode_offset + info->ucode_size,
			total_size);
		return -EINVAL;
	}

	/* verify CRC32 over the payload */
	{
		uint32_t computed = crc32_compute(buf + info->ucode_offset,
						  info->ucode_size);
		if (computed != info->crc32) {
			fprintf(stderr,
				"CRC mismatch: stored 0x%08X, computed 0x%08X\n",
				info->crc32, computed);
			return -EINVAL;
		}
	}

	return 0;
}

static int parse_gfx_header(const uint8_t *buf, struct fw_info *info)
{
	const struct gfx_firmware_header *hdr =
		(const struct gfx_firmware_header *)buf;

	if (info->header_size < sizeof(*hdr))
		return -EINVAL;

	info->gfx.feature_version = le32_to_cpu(hdr->ucode_feature_version);
	info->gfx.jt_offset       = le32_to_cpu(hdr->jt_offset);
	info->gfx.jt_size         = le32_to_cpu(hdr->jt_size);
	return 0;
}

static int parse_sdma_header(const uint8_t *buf, struct fw_info *info)
{
	const struct sdma_firmware_header *hdr =
		(const struct sdma_firmware_header *)buf;

	if (info->header_size < sizeof(*hdr))
		return -EINVAL;

	info->sdma.feature_version = le32_to_cpu(hdr->ucode_feature_version);
	info->sdma.ucode2_offset   = le32_to_cpu(hdr->ucode2_offset);
	info->sdma.ucode2_size     = le32_to_cpu(hdr->ucode2_size);
	return 0;
}

static int parse_rlc_header(const uint8_t *buf, struct fw_info *info)
{
	const struct rlc_firmware_header *hdr =
		(const struct rlc_firmware_header *)buf;

	if (info->header_size < sizeof(*hdr))
		return -EINVAL;

	info->rlc.feature_version    = le32_to_cpu(hdr->ucode_feature_version);
	info->rlc.save_restore_offset =
		le32_to_cpu(hdr->save_and_restore_offset);
	info->rlc.clear_state_offset  =
		le32_to_cpu(hdr->clear_state_descriptor_offset);
	info->rlc.scratch_locations   =
		le32_to_cpu(hdr->avail_scratch_ram_locations);
	return 0;
}

static int parse_smc_header(const uint8_t *buf, struct fw_info *info)
{
	const struct smc_firmware_header *hdr =
		(const struct smc_firmware_header *)buf;

	if (info->header_size < sizeof(*hdr))
		return -EINVAL;

	info->smc.ucode_start_addr = le32_to_cpu(hdr->ucode_start_addr);
	return 0;
}

/**
 * fw_parse_header - parse a GPU firmware binary image
 * @buf:     pointer to raw firmware bytes
 * @buf_len: size of @buf in bytes
 * @info:    output; populated on success
 *
 * Returns 0 on success, negative errno on error.
 */
int fw_parse_header(const uint8_t *buf, size_t buf_len, struct fw_info *info)
{
	int ret;

	if (!buf || !info)
		return -EINVAL;

	memset(info, 0, sizeof(*info));

	ret = parse_common_header(buf, buf_len, info);
	if (ret)
		return ret;

	switch (info->fw_type) {
	case FW_TYPE_GFX_ME:
	case FW_TYPE_GFX_PFP:
	case FW_TYPE_GFX_CE:
	case FW_TYPE_GFX_MEC:
		return parse_gfx_header(buf, info);
	case FW_TYPE_SDMA:
		return parse_sdma_header(buf, info);
	case FW_TYPE_RLC:
		return parse_rlc_header(buf, info);
	case FW_TYPE_SMC:
		return parse_smc_header(buf, info);
	default:
		fprintf(stderr, "unknown firmware type: 0x%02X\n", info->fw_type);
		return -EINVAL;
	}
}

/* ---------- pretty printer ----------------------------------- */
static void fw_print_info(const struct fw_info *info)
{
	printf("=== Firmware Header ===\n");
	printf("  type          : %s (0x%02X)\n",
	       fw_type_name(info->fw_type), info->fw_type);
	printf("  header ver    : %u.%u\n", info->ver_major, info->ver_minor);
	printf("  IP version    : %u.%u\n",
	       info->ip_ver_major, info->ip_ver_minor);
	printf("  ucode version : 0x%08X\n", info->ucode_version);
	printf("  total size    : %u bytes\n", info->total_size);
	printf("  ucode offset  : 0x%08X\n", info->ucode_offset);
	printf("  ucode size    : %u bytes\n", info->ucode_size);
	printf("  CRC-32        : 0x%08X  [OK]\n", info->crc32);

	switch (info->fw_type) {
	case FW_TYPE_GFX_ME:
	case FW_TYPE_GFX_PFP:
	case FW_TYPE_GFX_CE:
	case FW_TYPE_GFX_MEC:
		printf("  feature ver   : 0x%08X\n", info->gfx.feature_version);
		printf("  JT offset     : 0x%08X\n", info->gfx.jt_offset);
		printf("  JT size       : %u bytes\n", info->gfx.jt_size);
		break;
	case FW_TYPE_SDMA:
		printf("  feature ver   : 0x%08X\n", info->sdma.feature_version);
		printf("  ucode2 offset : 0x%08X\n", info->sdma.ucode2_offset);
		printf("  ucode2 size   : %u bytes\n", info->sdma.ucode2_size);
		break;
	case FW_TYPE_RLC:
		printf("  feature ver   : 0x%08X\n", info->rlc.feature_version);
		printf("  save/restore  : 0x%08X\n",
		       info->rlc.save_restore_offset);
		printf("  clear state   : 0x%08X\n",
		       info->rlc.clear_state_offset);
		break;
	case FW_TYPE_SMC:
		printf("  start addr    : 0x%08X\n", info->smc.ucode_start_addr);
		break;
	default:
		break;
	}
}

/* ---------- test helper: build a synthetic GFX firmware image  */
static size_t build_test_gfx_fw(uint8_t *buf, size_t buf_sz)
{
	struct gfx_firmware_header *hdr;
	const uint32_t payload[]  = {0xDEADBEEF, 0xCAFEBABE, 0x12345678};
	const uint32_t ucode_sz   = sizeof(payload);
	const uint32_t hdr_sz     = sizeof(*hdr);
	const uint32_t total_sz   = hdr_sz + ucode_sz;
	uint32_t crc;
	uint8_t *ucode_ptr;

	if (buf_sz < total_sz)
		return 0;

	memset(buf, 0, total_sz);
	hdr = (struct gfx_firmware_header *)buf;

	/* payload comes right after the header */
	ucode_ptr = buf + hdr_sz;
	memcpy(ucode_ptr, payload, ucode_sz);

	crc = crc32_compute(ucode_ptr, ucode_sz);

	/* fill common header (all LE) */
	hdr->common.magic                = cpu_to_le32(AMDGPU_FW_MAGIC);
	hdr->common.size_bytes           = cpu_to_le32(total_sz);
	hdr->common.header_size          = cpu_to_le32(hdr_sz);
	hdr->common.header_version_major = cpu_to_le32(1) & 0xFFFF;
	hdr->common.header_version_minor = 0;
	hdr->common.ip_version_major     = cpu_to_le32(9);
	hdr->common.ip_version_minor     = cpu_to_le32(0);
	hdr->common.ucode_version        = cpu_to_le32(0x01020304);
	hdr->common.ucode_size_bytes     = cpu_to_le32(ucode_sz);
	hdr->common.ucode_array_offset   = cpu_to_le32(hdr_sz);
	hdr->common.crc32                = cpu_to_le32(crc);
	hdr->common.fw_type              = FW_TYPE_GFX_ME;

	/* GFX-specific fields */
	hdr->ucode_feature_version = cpu_to_le32(0x00000012);
	hdr->jt_offset             = cpu_to_le32(hdr_sz);
	hdr->jt_size               = cpu_to_le32(8);

	return total_sz;
}

/* ---------- main --------------------------------------------- */
int main(void)
{
	uint8_t fw_buf[512];
	struct fw_info info;
	size_t fw_size;
	int ret;

	/* build a synthetic firmware image for testing */
	fw_size = build_test_gfx_fw(fw_buf, sizeof(fw_buf));
	if (!fw_size) {
		fprintf(stderr, "failed to build test firmware\n");
		return 1;
	}
	printf("built test firmware: %zu bytes\n\n", fw_size);

	/* parse it */
	ret = fw_parse_header(fw_buf, fw_size, &info);
	if (ret) {
		fprintf(stderr, "fw_parse_header failed: %d\n", ret);
		return 1;
	}

	fw_print_info(&info);

	/* tamper with CRC to verify detection */
	printf("\n--- tampering CRC ---\n");
	fw_buf[fw_size - 1] ^= 0xFF;
	ret = fw_parse_header(fw_buf, fw_size, &info);
	if (ret == -EINVAL)
		printf("CRC corruption detected correctly (ret=%d)\n", ret);

	return 0;
}

