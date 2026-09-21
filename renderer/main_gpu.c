#include "gpu.h"
#include "raster.h"

void render_frame(int frame);

/* -DDEMO_FRAME=n picks the frame for a single-shot render, so the host
 * reference and the simulated run can be pointed at the same one.
 * -DDEMO_LOOP instead animates forever, which is what you want on hardware. */
#ifndef DEMO_FRAME
#define DEMO_FRAME 0
#endif

/* Frame pacing for DEMO_LOOP. Without it the animation runs as fast as the
 * renderer can go, which is both faster than a display can show and variable
 * with scene complexity. */
#ifndef TARGET_FPS
#define TARGET_FPS 60
#endif
#define FRAME_US (1000000u / TARGET_FPS)

int main(void) {
    /* Guarded on the logical id: ids are handed out monotonically, so a
     * recycled slot never re-spawns. Warps then split the frame by row. */
    if (warpid() == 0) wspawn(NWARPS_R, (void*)0);

#ifdef DEMO_LOOP
    unsigned int next = TIMER_US + FRAME_US;
    for (int f = 0; ; f++) {
        render_frame(f);
        /* Each warp blits the rows it just drew, so no barrier is needed
         * between drawing and presenting. */
        raster_present();

        /* Keeps every warp on the same frame. Rows are owned exclusively so
         * this is not needed for correctness, but without it the warps drift
         * onto different frames and the display tears. */
        barrier(NWARPS_R);

        /* Signed difference so the comparison survives the timer's 32-bit
         * wrap, which happens every ~72 minutes. If a frame overran its
         * deadline, resync rather than sprinting to catch up -- chasing lost
         * time just makes the next few frames stutter. */
        if ((int)(TIMER_US - next) > 0) next = TIMER_US;
        else while ((int)(TIMER_US - next) < 0) { }
        next += FRAME_US;
    }
#else
    unsigned int t0 = TIMER_US;
    render_frame(DEMO_FRAME);
    unsigned int tr = TIMER_US;
    raster_present();
    unsigned int tp = TIMER_US;
    /* Every warp must present before any of them parks. A warp that finishes
     * early and spins on ALU ops never hits LSU backpressure, so it never
     * yields and the others never get scheduled -- their rows stay blank. */
    barrier(NWARPS_R);
    unsigned int t1 = TIMER_US;

    /* Reported before any barrier: rows are owned exclusively so a single
     * frame needs no barrier at all, and putting one here would hide a
     * failed wspawn as a hang instead of showing which warps finished. */
    say("warp  ", (unsigned int)warpid());
extern unsigned int g_clear_us, g_tri_us;
    say("clear ", g_clear_us);
    say("tris  ", g_tri_us);
    say("render", tr - t0);
    say("presnt", tp - tr);
    say("usec  ", t1 - t0);
    say("frame ", DEMO_FRAME);

    /* Deliberately not warp_flush(): the frame grabber abandons its vsync
     * alignment as soon as io_complete asserts, and the captured image comes
     * out rotated. Spinning holds the framebuffer stable. */
    for (;;) __asm__ volatile("nop");
#endif
}
