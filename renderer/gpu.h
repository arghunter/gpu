#ifndef GPU_H
#define GPU_H


#define NLANES      16
#define LANE_SHIFT   4               
#define NWARPS_MAX   4                 

#define LANE_ALL    (-1)



static inline int laneid(void) {
    int r; __asm__ volatile(".insn r 0x0B, 0, 0, %0, x0, x0" : "=r"(r)); return r;
}


static inline int warpid(void) {
    int r; __asm__ volatile(".insn r 0x0B, 0, 1, %0, x0, x0" : "=r"(r)); return r;
}


static inline int ballot(int p) {
    int r; __asm__ volatile(".insn r 0x0B, 0, 4, %0, %1, x0" : "=r"(r) : "r"(p)); return r;
}

static inline int tmc(int m) {
    int o; __asm__ volatile(".insn r 0x0B, 0, 5, %0, %1, x0" : "=r"(o) : "r"(m)); return o;
}

static inline void wspawn(int n, void* pc) {
    __asm__ volatile(".insn r 0x0B, 0, 6, x0, %0, %1" :: "r"(n), "r"(pc));
}

static inline void barrier(int n) {
    __asm__ volatile(".insn r 0x0B, 0, 7, x0, %0, x0" :: "r"(n) : "memory");
}


static inline void terminate(void) {
    __asm__ volatile(".insn r 0x0B, 0, 2, x0, x0, x0");
}


static inline int tid(void) { return (warpid() << LANE_SHIFT) | laneid(); }


#define PMOV(dst, src) __asm__("mv %0, %1" : "+r"(dst) : "r"(src))
#define PINC(dst)      __asm__("addi %0, %0, 1" : "+r"(dst))

#define MASKED(m) \
    for (int _gpu_om = tmc(m), _gpu_k = 0; !_gpu_k; _gpu_k = 1, tmc(_gpu_om))


#define FRAME_BUFFER   ((volatile unsigned int*)0x10000000)
#define SCREEN_W       320
#define SCREEN_H       240
#define TIMER_US       (*(volatile unsigned int*)0x08000004)
#define DEBUG_PUTCHAR  (*(volatile unsigned int*)0x70000000)
#define DEBUG_PUTNUM   (*(volatile unsigned int*)0x70000008)


static inline void putc_(char c) { DEBUG_PUTCHAR = (unsigned char)c; }
static inline void puts_(const char* s) { while (*s) putc_(*s++); }


static inline void hex_(unsigned int v) {
    for (int i = 7; i >= 0; i--) {
        unsigned int d = (v >> (i * 4)) & 0xF;
        putc_((char)(d < 10 ? ('0' + d) : ('A' + d - 10)));
    }
}


static inline void say(const char* label, unsigned int v) {
    MASKED(1) { puts_(label); hex_(v); putc_('\n'); }
}


__attribute__((noreturn)) static inline void warp_flush(void) {
    __asm__ volatile(
        "li t0, -1\n\t"
        ".insn r 0x0B, 0, 5, x0, t0, x0\n\t"
        "mv x1, x0\n\t"  "mv x2, x0\n\t"  "mv x3, x0\n\t"  "mv x4, x0\n\t"
        "mv x5, x0\n\t"  "mv x6, x0\n\t"  "mv x7, x0\n\t"  "mv x8, x0\n\t"
        "mv x9, x0\n\t"  "mv x10, x0\n\t" "mv x11, x0\n\t" "mv x12, x0\n\t"
        "mv x13, x0\n\t" "mv x14, x0\n\t" "mv x15, x0\n\t" "mv x16, x0\n\t"
        "mv x17, x0\n\t" "mv x18, x0\n\t" "mv x19, x0\n\t" "mv x20, x0\n\t"
        "mv x21, x0\n\t" "mv x22, x0\n\t" "mv x23, x0\n\t" "mv x24, x0\n\t"
        "mv x25, x0\n\t" "mv x26, x0\n\t" "mv x27, x0\n\t" "mv x28, x0\n\t"
        "mv x29, x0\n\t" "mv x30, x0\n\t" "mv x31, x0\n\t"
        ".insn r 0x0B, 0, 2, x0, x0, x0\n\t"
        "1: j 1b\n\t");
    __builtin_unreachable();
}

#endif 
