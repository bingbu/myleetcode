/*
HackerRank - Interview Preparation Kit
常考题目列表：
1. **实现 `memcpy`**：需处理内存重叠（Overlap）情况。
2. **实现 `memmove`**：与 `memcpy` 的区别及实现。
3. **实现 `strcpy` / `strncpy`**：注意 `\0` 终止符。
4. **实现 `atoi` / `itoa`**：处理溢出、空格及正负号。
5. **实现 `strstr`**：字符串匹配（KMP 优化）。
*/


#include <cstddef>
#include <climits>
#include <cstdio>
#include <cstring>
#include <cstdlib>

class Solution {
public:
#if 0
        int readl_poll_timeout_us(int sleep_us, int timeout_us, int sleep_before_op, void __iomem *addr)
        {
                ktime_t timeout = ktime_add_us(ktime_get(), timeout_us);
                int ret = 0;
                int val;

                if (sleep_us) 
                        usleep_range((sleep_us >> 2) + 1, sleep_us);
                for (;;) {
                        bool expired = timeout_us && ktime_compare(ktime_get(), timeout) > 0; 
                        barrier();
                        val = readl(addr);
                        if (val == 1)
                                return ret;
                        if (expired)
                                return -ETIMEDOUT;
                        if (sleep_us)
                                usleep_range((sleep_us >> 2) + 1, sleep_us);
                }

        }
#endif
        // 实现 `memcpy`需处理内存重叠（Overlap）情况
        void *myMemcpy(void* dest, const void* src, size_t n) {
            char* d = (char*)dest;
            const char* s = (const char*)src;
            while (n--)
                *d++ = *s++;
            return dest;
        }
        // 实现 `memmove`需处理内存重叠（Overlap）情况
        void *myMemmove(void* dest, const void* src, size_t n) {
	        char *d;
	        const char *s;
	        if (dest <= src) {
                        d = (char*)dest;
                        s = (const char*)src;
                        while (n--)
                                *d++ = *s++;
                } else {
                        d = (char*)dest + n;
                        s = (const char*)src + n;
                        while (n--)
                                *--d = *--s;
                }
                return dest;
        }
        /*实现 `strcpy`：注意 `\0` 终止符*/
        char *strcpy(char *dest, const char *src)
        {
                char *tmp = dest;
                while ((*tmp++ = *src++) != '\0')
                        /* nothing */;
                return dest;
        }
        /*实现 `strncpy`：注意 `\0` 终止符*/
        char *strncpy(char *dest, const char *src, size_t n)
        {
                char *tmp = dest;
                while (n-- && (*tmp++ = *src++) != '\0')
                        /* nothing */;
                if (n == 0)
                        *tmp = '\0';
                return dest;
        }
        /* 实现 `atoi`：处理integer overflow、空格及正负号。*/
        int atoi(const char *str) {
                int res = 0;
                int sign = 1;

                while (*str == ' ')
                        str++;

                if (*str == '+' || *str == '-') {
                        if (*str == '-')
                                sign = -1;
                        str++;
                }
                while (*str >= '0' && *str <= '9') {
                        int num = *str - '0';
                        /* use division to check overflow instead of multiplication */
                        if (res > (INT_MAX - num) / 10) {
                                return sign == 1 ? INT_MAX : INT_MIN;
                        }
                        res = res * 10 + num;
                        str++;
                }
                return res * sign;
        }

        /* 实现 `itoa`：处理integer overflow、空格及正负号。*/
        char *itoa(int value, char *str, int size) {
                snprintf(str, size, "%d", value);
                return str;
        }
        /* 实现 `strstr`：字符串匹配（KMP 优化）*/
        char *strstr(const char *s1, const char *s2) {
                int l1 = strlen(s1);
                int l2 = strlen(s2);
                if (l2 == 0)
                        return (char*)s1;
                while (l1 >= l2) {
                        if (!memcmp(s1, s2, l2))
                                return (char*)s1;
                        s1++;
                        l1--;
                }
                return nullptr;
        }

        /* 实现一个内核风格的find_next_zero_bit() */
        size_t find_next_zero_bit(const unsigned long *bitmap, size_t size, size_t offset) {
                const size_t bits_per_long = sizeof(unsigned long) * 8;
                size_t nwords = (size + bits_per_long - 1) / bits_per_long;

                if (offset >= size) 
                        return size;

                for (size_t i = offset / bits_per_long; i < nwords; i++) {
                        unsigned long word = ~bitmap[i];

                        /* The first word */
                        if (i == offset / bits_per_long)
                        word &= ~0UL << (offset & (bits_per_long - 1));
                        
                        /* The last word */
                        size_t rem = size & (bits_per_long - 1);
                        if (rem && i == nwords - 1)
                        word &= (1UL << rem) - 1;

                        if (word == 0) continue;

                        size_t bit = i * bits_per_long + __builtin_ctzl(word);
                        bit = bit < size ? bit : size;
                        return bit;
                }

                return size;
        }

        long long find_and_set_first_zero_bit(unsigned long *bitmap, size_t nbits) {
                size_t nwords;
                const size_t bits_per_long = sizeof(unsigned long) * 8;

                if (nbits == 0) 
                        return -1;

                nwords = (nbits + bits_per_long - 1) / bits_per_long;
                for (size_t i = 0; i < nwords; i++) {
                        unsigned long word = ~bitmap[i];
                        if (word == 0) 
                                continue;
                        
                        size_t bit = __builtin_ctzl(word);
                        if (bit + i * bits_per_long >= nbits) 
                                return -1;
                        bitmap[i] |= 1UL << bit;
                        return (long long)(bit + i * bits_per_long);
                }
                return -1;
        }

        long long find_and_set_first_zero_bit2(unsigned long *bitmap, size_t nbits) {
                const size_t bits_per_long = sizeof(unsigned long) * 8;

                if (nbits == 0) 
                        return -1;

                for (size_t i = 0; i < nbits; i++) {
                        size_t word_index = i / bits_per_long;
                        size_t bit_index = i % bits_per_long;
                        if ((bitmap[word_index] & (1UL << bit_index)) == 0) {
                                bitmap[word_index] |= 1UL << bit_index;
                                return (long long)i;
                        }
                }
                return -1;
        }

        void find_and_clear_bit(unsigned long *bitmap, size_t nbits, size_t bit) {
                if (bit >= nbits) 
                        return;

                const size_t bits_per_long = sizeof(unsigned long) * 8;
                size_t word_index = bit / bits_per_long;
                size_t offset = bit % bits_per_long;

                bitmap[word_index] &= ~(1UL << offset);
        }
};
int main() {
        Solution s;
        char src[] = "Hello, World!";
        char dest[20];
        s.myMemcpy(dest, src, sizeof(src));
        printf("myMemcpy: %s\n", dest);
        char dest2[20];
        s.myMemmove(dest2, src, sizeof(src));
        printf("myMemmove: %s\n", dest2);
        char dest3[20];
        s.strcpy(dest3, src);
        printf("strcpy: %s\n", dest3);
        char dest4[20];
        s.strncpy(dest4, src, sizeof(dest4));
        printf("strncpy: %s\n", dest4);

        printf("strstr: %s\n", strstr(src, "orld"));

        int num = s.atoi("   -12345");
        printf("atoi: %d\n", num);
        char str[20];
        s.itoa(12345, str, sizeof(str));
        printf("itoa: %s\n", str);
        

        return 0;

}
