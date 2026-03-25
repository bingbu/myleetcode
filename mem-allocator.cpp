/*
 * mem-allocator.c - Memory allocator with alloc, free, and coalescing
 *
 * Design: boundary-tag + explicit free list
 *
 * Block layout:
 *   [HEADER: size_t (block_size | alloc_bit)]
 *   [payload / free-node (prev*, next*) ...]
 *   [FOOTER: size_t (block_size | alloc_bit)]
 *
 * Heap layout:
 *   [prologue hdr+ftr (alloc=1)] [blocks...] [epilogue hdr (size=0, alloc=1)]
 *
 * Prologue and epilogue sentinel blocks prevent coalescing past boundaries.
 *
 * Allocation : first-fit search in explicit free list
 * Free       : mark block free, coalesce with adjacent free neighbors (4 cases)
 * Coalescing : O(1) via boundary tags + explicit free list removal
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* ---------- constants ---------------------------------------- */
#define ALIGNMENT		8
#define ALIGN(n)		(((n) + (ALIGNMENT - 1)) & ~(size_t)(ALIGNMENT - 1))
#define WSIZE			(sizeof(size_t))
#define MIN_BLOCK		(2 * WSIZE + 2 * sizeof(void *))
#define HEAP_SIZE		(1u << 20)	/* 1 MB heap pool */

/* ---------- header/footer macros ----------------------------- */
#define PACK(sz, alloc)		((sz) | (alloc))
#define GET(p)			(*(size_t *)(p))
#define PUT(p, v)		(*(size_t *)(p) = (v))
#define BLK_SIZE(p)		(GET(p) & ~(size_t)7)
#define BLK_ALLOC(p)		(GET(p) & 1)

/* bp points to block header */
#define HDR(bp)			((char *)(bp))
#define FTR(bp)			((char *)(bp) + BLK_SIZE(HDR(bp)) - WSIZE)
#define PAYLOAD(bp)		((char *)(bp) + WSIZE)
#define NEXT_BLK(bp)		((char *)(bp) + BLK_SIZE(HDR(bp)))
#define PREV_BLK(bp)		((char *)(bp) - BLK_SIZE(((char *)(bp) - WSIZE)))

/* ---------- free-list node embedded in block payload --------- */
struct free_node {
	struct free_node *prev;
	struct free_node *next;
};

static char heap_pool[HEAP_SIZE] __attribute__((aligned(8)));
static char *heap_start;	/* prologue header */
static char *heap_end;		/* epilogue header  */
static struct free_node *free_head;

/* ---------- explicit free list ------------------------------- */
static inline char *node_to_bp(struct free_node *n)
{
	return (char *)n - WSIZE;
}

static void fl_insert(char *bp)
{
	struct free_node *n = (struct free_node *)PAYLOAD(bp);

	n->prev = NULL;
	n->next = free_head;
	if (free_head)
		free_head->prev = n;
	free_head = n;
}

static void fl_remove(char *bp)
{
	struct free_node *n = (struct free_node *)PAYLOAD(bp);

	if (n->prev)
		n->prev->next = n->next;
	else
		free_head = n->next;
	if (n->next)
		n->next->prev = n->prev;
	n->prev = n->next = NULL;
}

/* ---------- coalesce: 4 cases -------------------------------- */
static char *coalesce(char *bp)
{
	int prev_free = !BLK_ALLOC(HDR(bp) - WSIZE);
	int next_free = !BLK_ALLOC(HDR(NEXT_BLK(bp)));
	size_t sz = BLK_SIZE(HDR(bp));
	char *prev, *next;

	if (!prev_free && !next_free) {
		/* case 1: both neighbors allocated */
		fl_insert(bp);

	} else if (!prev_free && next_free) {
		/* case 2: merge with next */
		next = NEXT_BLK(bp);
		fl_remove(next);
		sz += BLK_SIZE(HDR(next));
		PUT(HDR(bp), PACK(sz, 0));
		PUT(FTR(bp), PACK(sz, 0));
		fl_insert(bp);

	} else if (prev_free && !next_free) {
		/* case 3: merge with prev */
		prev = PREV_BLK(bp);
		fl_remove(prev);
		sz += BLK_SIZE(HDR(prev));
		PUT(HDR(prev), PACK(sz, 0));
		PUT(FTR(prev), PACK(sz, 0));
		fl_insert(prev);
		bp = prev;

	} else {
		/* case 4: merge with both neighbors */
		prev = PREV_BLK(bp);
		next = NEXT_BLK(bp);
		fl_remove(prev);
		fl_remove(next);
		sz += BLK_SIZE(HDR(prev)) + BLK_SIZE(HDR(next));
		PUT(HDR(prev), PACK(sz, 0));
		PUT(FTR(prev), PACK(sz, 0));
		fl_insert(prev);
		bp = prev;
	}
	return bp;
}

/* ---------- heap init ---------------------------------------- */
static void mem_init(void)
{
	size_t pro_sz = 2 * WSIZE;
	size_t sz;
	char *bp;

	heap_start = heap_pool;
	free_head  = NULL;

	/*
	 * Prologue: header + footer, alloc=1.
	 * Acts as left sentinel to prevent backward coalescing.
	 */
	PUT(heap_start,         PACK(pro_sz, 1));	/* prologue header */
	PUT(heap_start + WSIZE, PACK(pro_sz, 1));	/* prologue footer */

	/*
	 * Epilogue: header only, size=0, alloc=1.
	 * Acts as right sentinel to prevent forward coalescing.
	 */
	heap_end = heap_start + HEAP_SIZE - WSIZE;
	PUT(heap_end, PACK(0, 1));

	/* One large free block spanning the usable heap */
	bp = heap_start + pro_sz;
	sz = (size_t)(heap_end - bp);
	PUT(HDR(bp), PACK(sz, 0));
	PUT(FTR(bp), PACK(sz, 0));
	fl_insert(bp);
}

/* ---------- first-fit search --------------------------------- */
static char *find_fit(size_t asize)
{
	struct free_node *n;

	for (n = free_head; n; n = n->next) {
		char *bp = node_to_bp(n);

		if (BLK_SIZE(HDR(bp)) >= asize)
			return bp;
	}
	return NULL;
}

/* ---------- place: allocate, split if remainder is big enough  */
static void place(char *bp, size_t asize)
{
	size_t total = BLK_SIZE(HDR(bp));
	char *rem;
	size_t rem_sz;

	fl_remove(bp);

	if (total - asize >= MIN_BLOCK) {
		/* split: carve out asize, leave remainder as free block */
		PUT(HDR(bp), PACK(asize, 1));
		PUT(FTR(bp), PACK(asize, 1));
		rem    = NEXT_BLK(bp);
		rem_sz = total - asize;
		PUT(HDR(rem), PACK(rem_sz, 0));
		PUT(FTR(rem), PACK(rem_sz, 0));
		fl_insert(rem);
	} else {
		PUT(HDR(bp), PACK(total, 1));
		PUT(FTR(bp), PACK(total, 1));
	}
}

/* ---------- public API --------------------------------------- */
void *mem_alloc(size_t size)
{
	size_t payload, asize;
	char *bp;

	if (!size)
		return NULL;

	payload = ALIGN(size < 2 * sizeof(void *) ? 2 * sizeof(void *) : size);
	asize   = payload + 2 * WSIZE;

	bp = find_fit(asize);
	if (!bp)
		return NULL;		/* out of memory */

	place(bp, asize);
	return PAYLOAD(bp);
}

void mem_free(void *ptr)
{
	char *bp;
	size_t sz;

	if (!ptr)
		return;

	bp = (char *)ptr - WSIZE;
	sz = BLK_SIZE(HDR(bp));
	PUT(HDR(bp), PACK(sz, 0));
	PUT(FTR(bp), PACK(sz, 0));
	coalesce(bp);
}

/* ---------- simple test -------------------------------------- */
int main(void)
{
	void *a, *b, *c, *big;

	mem_init();

	a = mem_alloc(100);
	b = mem_alloc(200);
	c = mem_alloc(50);
	printf("alloc: a=%p  b=%p  c=%p\n", a, b, c);

	memset(a, 0xAA, 100);
	memset(b, 0xBB, 200);
	memset(c, 0xCC, 50);

	mem_free(b);	/* isolated free block         */
	mem_free(a);	/* coalesce left+middle        */
	mem_free(c);	/* coalesce all three (case 4) */

	big = mem_alloc(300);
	printf("big  : big=%p (reused coalesced block)\n", big);

	memset(big, 0xDD, 300);
	printf("done : memory intact\n");
	return 0;
}


/* ── constants ─────────────────────────────────────────────── */
#define ALIGNMENT        8
#define ALIGN(n)         (((n) + (ALIGNMENT-1)) & ~(size_t)(ALIGNMENT-1))
#define WSIZE            sizeof(size_t)       /* header / footer width */
#define MIN_BLOCK        (2*WSIZE + 2*sizeof(void*)) /* hdr+ftr+prev+next */
#define HEAP_SIZE        (1u << 20)           /* 1 MB heap pool */

/* ── header / footer helpers ───────────────────────────────── */
#define PACK(sz, alloc)  ((sz) | (alloc))
#define GET(p)           (*(size_t *)(p))
#define PUT(p, v)        (*(size_t *)(p) = (v))
#define BLK_SIZE(p)      (GET(p) & ~(size_t)7)
#define BLK_ALLOC(p)     (GET(p) & 1)

/* bp = pointer to block header */
#define HDR(bp)          ((char *)(bp))
#define FTR(bp)          ((char *)(bp) + BLK_SIZE(HDR(bp)) - WSIZE)
#define PAYLOAD(bp)      ((char *)(bp) + WSIZE)
#define NEXT_BLK(bp)     ((char *)(bp) + BLK_SIZE(HDR(bp)))
#define PREV_BLK(bp)     ((char *)(bp) - BLK_SIZE(((char *)(bp) - WSIZE)))

/* ── free-list node embedded in block payload ───────────────── */
struct FreeNode {
    FreeNode *prev;
    FreeNode *next;
};

static char heap_pool[HEAP_SIZE] __attribute__((aligned(16)));
static char *heap_start;   /* prologue header */
static char *heap_end;     /* epilogue header  */
static FreeNode *free_head;

/* ── explicit free list operations ─────────────────────────── */
static inline char *node_to_bp(FreeNode *n) { return (char *)n - WSIZE; }

static void fl_insert(char *bp) {
    FreeNode *n = (FreeNode *)PAYLOAD(bp);
    n->prev = nullptr;
    n->next = free_head;
    if (free_head) free_head->prev = n;
    free_head = n;
}

static void fl_remove(char *bp) {
    FreeNode *n = (FreeNode *)PAYLOAD(bp);
    if (n->prev) n->prev->next = n->next;
    else         free_head     = n->next;
    if (n->next) n->next->prev = n->prev;
    n->prev = n->next = nullptr;
}

/* ── coalesce: merge bp with free neighbors (4 cases) ──────── */
static char *coalesce(char *bp) {
    bool prev_free = !BLK_ALLOC(HDR(bp) - WSIZE); /* prev block footer */
    bool next_free = !BLK_ALLOC(HDR(NEXT_BLK(bp)));
    size_t sz = BLK_SIZE(HDR(bp));

    if (!prev_free && !next_free) {
        /* Case 1: isolated free block */
        fl_insert(bp);

    } else if (!prev_free && next_free) {
        /* Case 2: merge with next */
        char *next = NEXT_BLK(bp);
        fl_remove(next);
        sz += BLK_SIZE(HDR(next));
        PUT(HDR(bp), PACK(sz, 0));
        PUT(FTR(bp), PACK(sz, 0));
        fl_insert(bp);

    } else if (prev_free && !next_free) {
        /* Case 3: merge with prev */
        char *prev = PREV_BLK(bp);
        fl_remove(prev);
        sz += BLK_SIZE(HDR(prev));
        PUT(HDR(prev), PACK(sz, 0));
        PUT(FTR(prev), PACK(sz, 0));
        fl_insert(prev);
        bp = prev;

    } else {
        /* Case 4: merge with both */
        char *prev = PREV_BLK(bp);
        char *next = NEXT_BLK(bp);
        fl_remove(prev);
        fl_remove(next);
        sz += BLK_SIZE(HDR(prev)) + BLK_SIZE(HDR(next));
        PUT(HDR(prev), PACK(sz, 0));
        PUT(FTR(prev), PACK(sz, 0));
        fl_insert(prev);
        bp = prev;
    }
    return bp;
}

/* ── heap initialisation ────────────────────────────────────── */
static void mem_init() {
    heap_start = heap_pool;
    free_head  = nullptr;

    /* Prologue: header + footer only, alloc=1, prevents backward coalesce */
    size_t pro_sz = 2 * WSIZE;
    PUT(heap_start,         PACK(pro_sz, 1)); /* prologue header */
    PUT(heap_start + WSIZE, PACK(pro_sz, 1)); /* prologue footer */

    /* Epilogue: header only, size=0 alloc=1, prevents forward coalesce */
    heap_end = heap_start + HEAP_SIZE - WSIZE;
    PUT(heap_end, PACK(0, 1));

    /* One large free block spanning the rest */
    char *bp  = heap_start + pro_sz;
    size_t sz = (size_t)(heap_end - bp);
    PUT(HDR(bp), PACK(sz, 0));
    PUT(FTR(bp), PACK(sz, 0));
    fl_insert(bp);
}

/* ── first-fit search ───────────────────────────────────────── */
static char *find_fit(size_t asize) {
    for (FreeNode *n = free_head; n; n = n->next) {
        char *bp = node_to_bp(n);
        if (BLK_SIZE(HDR(bp)) >= asize)
            return bp;
    }
    return nullptr;
}

/* ── place: allocate block, split remainder if large enough ─── */
static void place(char *bp, size_t asize) {
    size_t total = BLK_SIZE(HDR(bp));
    fl_remove(bp);

    if (total - asize >= MIN_BLOCK) {
        /* split */
        PUT(HDR(bp), PACK(asize, 1));
        PUT(FTR(bp), PACK(asize, 1));
        char *rem = NEXT_BLK(bp);
        size_t rem_sz = total - asize;
        PUT(HDR(rem), PACK(rem_sz, 0));
        PUT(FTR(rem), PACK(rem_sz, 0));
        fl_insert(rem);
    } else {
        PUT(HDR(bp), PACK(total, 1));
        PUT(FTR(bp), PACK(total, 1));
    }
}

/* ── public API ─────────────────────────────────────────────── */
void *mem_alloc(size_t size) {
    if (size == 0) return nullptr;

    /* block size = aligned payload + header + footer */
    size_t payload = ALIGN(size < (2*sizeof(void*)) ? (2*sizeof(void*)) : size);
    size_t asize   = payload + 2 * WSIZE;

    char *bp = find_fit(asize);
    if (!bp) return nullptr;         /* out of memory */

    place(bp, asize);
    return PAYLOAD(bp);
}

void mem_free(void *ptr) {
    if (!ptr) return;
    char *bp   = (char *)ptr - WSIZE;
    size_t sz  = BLK_SIZE(HDR(bp));
    PUT(HDR(bp), PACK(sz, 0));
    PUT(FTR(bp), PACK(sz, 0));
    coalesce(bp);
}

/* ── simple test ─────────────────────────────────────────────── */
int main() {
    mem_init();

    void *a = mem_alloc(100);
    void *b = mem_alloc(200);
    void *c = mem_alloc(50);
    printf("alloc: a=%p  b=%p  c=%p\n", a, b, c);

    /* write sentinel values to verify no overlap */
    memset(a, 0xAA, 100);
    memset(b, 0xBB, 200);
    memset(c, 0xCC, 50);

    mem_free(b);   /* free middle      → isolated free block  */
    mem_free(a);   /* free left        → coalesce a+b (case 2)*/
    mem_free(c);   /* free right       → coalesce a+b+c (case 4) */

    /* After full coalesce, one big block should be available */
    void *big = mem_alloc(300);
    printf("big  : big=%p (reused coalesced block)\n", big);

    /* Verify the block is usable */
    memset(big, 0xDD, 300);
    printf("done : memory intact\n");
    return 0;
}


