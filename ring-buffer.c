#include <cstddef>
#include <climits>
#include <cstdio>
#include <cstring>
#include <cstdlib>


#define rmb()  __asm__ __volatile__("" ::: "memory")
#define wmb()  __asm__ __volatile__("" ::: "memory")
#define READ_ONCE(x)       __atomic_load_n(&(x), __ATOMIC_ACQUIRE)
#define WRITE_ONCE(x, val) __atomic_store_n(&(x), (val), __ATOMIC_RELEASE)

/* 实现一个 lock-free 或简单线程安全的 ring buffer */
struct ring_buffer {
    void **buf;
    size_t capacity;
    size_t read;
    size_t write;
};

int push(struct ring_buffer *rb, void *item) {
        if (!rb->capacity)
            return -1;

        size_t write = READ_ONCE(rb->write);
        if ((write + 1) % rb->capacity == READ_ONCE(rb->read)) {
            return -1; // buffer full
        }
        rb->buf[write] = item;
        wmb();
        WRITE_ONCE(rb->write, (write + 1) % rb->capacity);

        return 0;
}

int pop(struct ring_buffer *rb, void **item) {
        if (!rb->capacity)
            return -1;

        size_t read = READ_ONCE(rb->read);
        if (read == READ_ONCE(rb->write)) {
            return -1; // buffer empty
        }
        rmb();
        *item = rb->buf[read];
        WRITE_ONCE(rb->read, (read + 1) % rb->capacity);

        return 0;
}