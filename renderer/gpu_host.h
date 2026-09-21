#ifndef GPU_HOST_H
#define GPU_HOST_H

/* Host stand-in for the SIMT intrinsics.
 *
 * Compiling the renderer natively with NLANES == 1 gives a ground-truth image
 * in milliseconds instead of minutes, and any difference from the simulated
 * render localises immediately to the SIMT path rather than the maths. Build
 * with -DGPU_HOST.
 *
 * NLANES is 1 here on purpose: a scalar reference cannot disagree with itself
 * about lane behaviour, which is exactly what makes it a reference. */

#include <stdio.h>
#include <stdlib.h>

#define NLANES      1
#define LANE_SHIFT  0
#define NWARPS_MAX  1
#define LANE_ALL    (-1)

static inline int  laneid(void) { return 0; }
static inline int  warpid(void) { return 0; }
static inline int  tid(void)    { return 0; }
static inline int  ballot(int p){ return p ? 1 : 0; }
static inline int  tmc(int m)   { (void)m; return 1; }
static inline void wspawn(int n, void* pc) { (void)n; (void)pc; }
static inline void barrier(int n)          { (void)n; }
static inline void terminate(void)         { }

#define PMOV(dst, src) ((dst) = (src))
#define PINC(dst)      ((dst)++)

/* Runs the body iff lane 0 is enabled, which with one lane is the whole of
 * the semantics. */
#define MASKED(m) for (int _gpu_k = ((m) & 1), _gpu_i = 0; _gpu_k && !_gpu_i; _gpu_i = 1)

/* No hardware timer on the host; renders are instant and untimed. */
#define TIMER_US 0u

#define SCREEN_W 320
#define SCREEN_H 240

extern unsigned int host_fb[SCREEN_W * SCREEN_H];
#define FB host_fb

static inline void putc_(char c) { fputc(c, stdout); }
static inline void puts_(const char* s) { while (*s) putc_(*s++); }
static inline void hex_(unsigned int v) {
    for (int i = 7; i >= 0; i--) {
        unsigned int d = (v >> (i * 4)) & 0xF;
        putc_((char)(d < 10 ? ('0' + d) : ('A' + d - 10)));
    }
}
static inline void say(const char* label, unsigned int v) {
    puts_(label); hex_(v); putc_('\n');
}
__attribute__((noreturn)) static inline void warp_flush(void) { exit(0); }

#endif /* GPU_HOST_H */
