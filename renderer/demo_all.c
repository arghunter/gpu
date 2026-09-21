#include "gpu.h"
#include "raster.h"

/* Both demos, alternating on a fixed schedule.
 *
 * The three scenes stress different parts of the machine -- demo_spin is a
 * triangle rasteriser bound on the depth-buffer read-modify-write, demo_phys
 * is register-resident particle integration that barely touches memory, and
 * demo_fluid is an O(N^2) SPH sweep bound on arithmetic -- so running them
 * back to back shows all three without rebuilding.
 *
 * demo_fluid does not hold 60 fps at 512 particles (~43 ms a frame). Its
 * pacing resyncs rather than trying to catch up, so it simply runs slower;
 * the scene deadline is wall-clock, so its turn is still 20 seconds.
 *
 * Scenes are switched on a wall-clock deadline rather than a frame count,
 * because neither scene is guaranteed to hold 60 fps -- the rasteriser does
 * not, so counting frames would stretch its turn well past the interval.
 *
 * Only warp 0 reads the clock and decides; the barrier at the bottom of the
 * frame publishes that decision to the other three. Four independent
 * TIMER_US reads would disagree, and a warp left behind in a scene blocks on
 * a barrier the departed warps never reach. */

#ifndef TARGET_FPS
#define TARGET_FPS 60
#endif
#define FRAME_US (1000000u / TARGET_FPS)

#ifndef SCENE_SECS
#define SCENE_SECS 20
#endif

void render_frame(int frame);        /* demo_spin */
void phys_scene(unsigned int secs);  /* demo_phys */
void fluid_scene(unsigned int secs); /* demo_fluid */

static volatile int g_spin_end;

int main(void) {
    /* Spawned once here, not per scene: warp slots only free on terminate,
     * and neither scene terminates. */
    if (warpid() == 0) wspawn(NWARPS_R, (void*)0);

    for (;;) {
        unsigned int next = TIMER_US + FRAME_US;
        unsigned int end  = TIMER_US + SCENE_SECS * 1000000u;
        for (int f = 0; ; f++) {
            render_frame(f);
            /* Warps own interleaved rows here, so each blits the rows it just
             * drew and no barrier is needed in between. */
            raster_present();

            /* Paced in warp 0 only. The spin is pure ALU and this scheduler
             * switches warps on a memory stall, a barrier or terminate --
             * four warps spinning would each hold the pipeline for a full
             * slice. The others yield in the barrier instead. */
            if (warpid() == 0) {
                if ((int)(TIMER_US - next) > 0) next = TIMER_US;
                else while ((int)(TIMER_US - next) < 0) { }
                next += FRAME_US;
                g_spin_end = ((int)(TIMER_US - end) >= 0);
            }
            barrier(NWARPS_R);
            if (g_spin_end) break;
        }

        /* Each owns its own paced loop -- the particle state has to stay in
         * registers across frames, so the loop cannot live out here. */
        phys_scene(SCENE_SECS);
        fluid_scene(SCENE_SECS);
    }
}
