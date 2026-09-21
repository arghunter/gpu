#ifndef GPU_H
#define GPU_H

/* -DGPU_HOST swaps in a scalar native implementation; see gpu_host.h. */
#ifdef GPU_HOST
#include "gpu_host.h"
#else


/* Overridable so the GPU can be built scalar (-DNLANES=1) without touching
 * the RTL: every lane then runs identical code and writes identical
 * addresses, which isolates a vectorisation bug from an arithmetic one. */
#ifndef NLANES
#define NLANES      16
#endif
#define LANE_SHIFT   4               
#define NWARPS_MAX   4                 

#define LANE_ALL    (-1)



/* Forced to 0 when the code is built scalar. The instruction still reports
 * the real hardware lane, so without this a -DNLANES=1 build on 16-lane
 * hardware has every lane seed itself at a different column while striding by
 * one -- lanes then overlap and the image is wrong in a way that looks like a
 * rasteriser bug. */
static inline int laneid(void) {
#if NLANES == 1
    return 0;
#else
    int r; __asm__ volatile(".insn r 0x0B, 0, 0, %0, x0, x0" : "=r"(r)); return r;
#endif
}


static inline int warpid(void) {
    int r; __asm__ volatile(".insn r 0x0B, 0, 1, %0, x0, x0" : "=r"(r)); return r;
}


static inline int ballot(int p) {
    int r; __asm__ volatile(".insn r 0x0B, 0, 4, %0, %1, x0" : "=r"(r) : "r"(p)); return r;
}

/* The "memory" clobber is load-bearing. tmc changes which lanes commit, so
 * GCC must not move a load or store across it -- hoisting a masked load above
 * the narrowing makes inactive lanes touch memory, and sinking a masked store
 * below the restore writes pixels that should have been masked off. Without
 * it the compiler is free to do both, and the host reference cannot reproduce
 * the result because it has no mask at all. */
static inline int tmc(int m) {
    int o; __asm__ volatile(".insn r 0x0B, 0, 5, %0, %1, x0" : "=r"(o) : "r"(m) : "memory"); return o;
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

/* Scoped execution mask.
 *
 * Two hazards, both of which only appear when the mask is narrow:
 *
 * 1. An all-zero mask is fatal. With no lane enabled NO register write
 *    commits, so no loop counter can change and no branch can observe a new
 *    value -- the restoring tmc never runs and the warp stays masked off
 *    permanently. The && short-circuits before tmc is ever called, so a
 *    zero mask simply skips the block, which is the same thing semantically
 *    and cannot wedge.
 *
 * 2. The counter must be written AFTER the mask is restored. The exit branch
 *    reads rs1_val of the first active lane; if the counter were set while
 *    still narrowed, a lane outside the mask could hold a stale value and
 *    run the body twice.
 *
 * Everything the condition depends on is therefore evaluated either before
 * narrowing or after restoring. */
#define MASKED(m) \
    for (int _gpu_m = (m), _gpu_om = 0, _gpu_k = 0; \
         _gpu_m && !_gpu_k && (_gpu_om = tmc(_gpu_m), 1); \
         tmc(_gpu_om), _gpu_k = 1)

#define FRAME_BUFFER   ((volatile unsigned int*)0x10000000)
/* Write-only: anything >= 0x10000000 is MMIO, loads return bypass values. */
#define FB             FRAME_BUFFER
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

#endif /* GPU_HOST */

#endif 
