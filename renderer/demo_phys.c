#include "gpu.h"
#include "camera.h"
#include "raster.h"

/* 3D particle physics: one particle per thread, all state in registers.
 *
 * This suits the machine far better than the rasteriser does. Particles are
 * completely independent, so there is no shared state and nothing that would
 * need atomics this hardware does not have. The per-particle state lives in
 * registers, so a frame costs ~2 stores per thread instead of the ~230k the
 * renderer spends clearing and blitting.
 *
 * It also exercises the part of the ISA that a rasteriser cannot: collision
 * against six box walls is six independent divergent conditions per particle,
 * handled with ballot + MASKED + PMOV and no branches at all.
 *
 * Its own main() rather than render_frame(): the particle state has to
 * persist across frames, and it only stays in registers if the loop is
 * inside the function that owns it. Build with ENTRY= . */

/* Draw into the rasteriser's back buffer rather than the display. The VGA
 * scans out continuously, so painting the sky straight into it means the beam
 * catches a half-erased frame -- which is the flicker. This buffer is already
 * linked in via raster.c and unused here, so reusing it costs no memory. */
#define BB raster_fb

#ifndef NWARPS_P
#define NWARPS_P 4
#endif
/* Particles per thread. Each thread's set stays in registers (or at worst
 * its own stack), so raising this scales the simulation without introducing
 * any sharing between threads. 4 x 64 threads = 256 particles. */
#ifndef PPT
#define PPT 4
#endif
/* Both scenes are spawned once by whoever owns main(), so the two warp
 * counts have to agree -- a mismatch makes one scene's barrier wait on a
 * warp that is not coming. */
_Static_assert(NWARPS_P == NWARPS_R, "scene warp counts must match");
#define NTHREAD (NWARPS_P * NLANES)
#define NPART   (NTHREAD * PPT)

#ifndef TARGET_FPS
#define TARGET_FPS 60
#endif
#define FRAME_US (1000000u / TARGET_FPS)

#define BG        0x080810
#define WALL      FX(3)
#define FLOOR     FX(-2)
#define CEIL      FX(4)
#define GRAVITY   FX_FRAC(-7, 1000)
#define REST_F    FX_FRAC(80, 100)      /* floor is lossier than the walls */
#define REST_W    FX_FRAC(92, 100)
#define ORBIT_R   10

static unsigned int hash(unsigned int x) {
    x ^= x << 13; x ^= x >> 17; x ^= x << 5; return x;
}

/* Every lane computes the address; only the in-bounds ones store. A plain
 * `if` here would be a per-lane branch, which is exactly what the mask is
 * for -- and the clamped index keeps inactive lanes from forming an
 * out-of-range address at all. */
static inline void put(int x, int y, unsigned int c) {
    int ok  = ((unsigned)x < SCREEN_W) && ((unsigned)y < SCREEN_H);
    int idx = ok ? (y * SCREEN_W + x) : 0;
    MASKED(ballot(ok)) { BB[idx] = c; }
}

/* A vertical gradient costs exactly what a flat clear costs -- one store per
 * pixel -- and gives the scene a horizon to sit against. Redrawing the whole
 * background every frame also means neither the particles nor the box need
 * their previous positions tracked for erasing. At ~1300 us it is 8% of a
 * 60 fps budget, which is worth it for the simplification alone. */
static void draw_background(void) {
    const int lane = laneid();
    const int warp = warpid() & (NWARPS_P - 1);
    for (int y = warp; y < SCREEN_H; y += NWARPS_P) {
        /* Per row, so the divides are amortised over 320 pixels. */
        unsigned int k = (unsigned int)y;
        unsigned int r = 2 + (k * 12) / SCREEN_H;
        unsigned int g = 3 + (k * 18) / SCREEN_H;
        unsigned int b = 8 + (k * 34) / SCREEN_H;
        int base = y * SCREEN_W;
        for (int x = lane; x < SCREEN_W; x += NLANES) {
            /* The VGA keeps only the top nibble of each channel, so a subtle
             * gradient collapses into three flat bands. A 4x4 ordered dither
             * added to the low bits makes the carry into that nibble
             * probabilistic, which reads as a smooth ramp. Computed rather
             * than looked up: a table index varies per lane, and this LSU
             * would turn that into 16 separate transactions. */
            unsigned int d = (unsigned int)(((x & 1) << 3) | ((y & 1) << 2)
                                          |  (x & 2)       | ((y & 2) >> 1));
            BB[base + x] = ((r + d) << 16) | ((g + d) << 8) | (b + d);
        }
    }
}

/* Box corners, then the 12 edges, then a floor grid. 24 segments x 16 samples
 * is 384 points, which divides evenly by the thread count at any warp count
 * -- so the sampling loop has a warp-uniform trip count and needs no masking. */
#define SEG_SAMP  16
#define N_BOX_E   12
#define N_GRID    12
#define N_SEG     (N_BOX_E + N_GRID)
#define NPART_UNUSED 0

static const signed char box_e[N_BOX_E][2] = {
    {0,1},{1,2},{2,3},{3,0},   {4,5},{5,6},{6,7},{7,4},   {0,4},{1,5},{2,6},{3,7},
};

static void corner(int i, vec3* o) {
    *o = v3((i == 1 || i == 2 || i == 5 || i == 6) ?  WALL : -WALL,
            (i < 4) ? FLOOR : CEIL,
            (i == 2 || i == 3 || i == 6 || i == 7) ?  WALL : -WALL);
}

/* Segment endpoints: box edges first, then grid lines lying on the floor. */
static void segment(int s, vec3* a, vec3* b) {
    if (s < N_BOX_E) {
        corner(box_e[s][0], a);
        corner(box_e[s][1], b);
    } else {
        int g = s - N_BOX_E;
        int i = g % 6;
        fx u = -WALL + fx_mul(FX_FRAC(i, 5), FX(2) * 3);   /* 6 lines across 2*WALL */
        if (g < 6) { *a = v3(u, FLOOR, -WALL); *b = v3(u, FLOOR,  WALL); }
        else       { *a = v3(-WALL, FLOOR, u); *b = v3( WALL, FLOOR, u); }
    }
}

static unsigned int shade(unsigned int c, fx k) {
    unsigned int r = (c >> 16) & 0xFF, g = (c >> 8) & 0xFF, b = c & 0xFF;
    r = (unsigned int)(((long long)r * k) >> FX_SHIFT);
    g = (unsigned int)(((long long)g * k) >> FX_SHIFT);
    b = (unsigned int)(((long long)b * k) >> FX_SHIFT);
    return (r << 16) | (g << 8) | b;
}

/* Shared projection: returns 0 behind the eye. iw doubles as the depth cue --
 * nearer things get brighter. */
static int project(const mat4* vp, vec3 p, int* sx, int* sy, fx* iw_out) {
    vec4 c = mat4_mul_point(vp, p);
    if (c.w <= FX_FRAC(1, 4)) return 0;
    fx iw = fx_div(FX_ONE, c.w);
    fx nx = fx_mul(c.x, iw), ny = fx_mul(c.y, iw);
    *sx = fx_round_int(fx_mul(nx + FX_ONE, FX(SCREEN_W / 2)));
    *sy = fx_round_int(fx_mul(FX_ONE - ny, FX(SCREEN_H / 2)));
    *iw_out = iw;
    return 1;
}

static void draw_box(const mat4* vp) {
    for (int k = tid(); k < N_SEG * SEG_SAMP; k += NTHREAD) {
        int s = k / SEG_SAMP, i = k % SEG_SAMP;
        vec3 a, b;
        segment(s, &a, &b);
        vec3 p = v3_lerp(a, b, FX_FRAC(i, SEG_SAMP));

        int sx, sy; fx iw;
        int ok = project(vp, p, &sx, &sy, &iw);
        /* Grid dimmer than the box frame, and everything fades with distance
         * so the far wall reads as further away. */
        fx k2 = fx_clamp(fx_mul(iw, FX(13)), FX_FRAC(45,100), FX_ONE);
        unsigned int c = shade(s < N_BOX_E ? 0x70D0FF : 0x3070A0, k2);
        MASKED(ballot(ok)) { put(sx, sy, c); }
    }
}

static unsigned int part_colour(int t) {
    unsigned int h = hash((unsigned)t * 2654435761u);
    unsigned int r = 0x60 + (h & 0x9F);
    unsigned int g = 0x60 + ((h >> 8) & 0x9F);
    unsigned int b = 0x60 + ((h >> 16) & 0x9F);
    return (r << 16) | (g << 8) | b;
}

/* One warp decides when the scene is over and the barrier publishes the
 * decision, so all four leave on the same frame. Reading TIMER_US
 * independently per warp would not do: the reads differ, and a warp that
 * stayed behind would block on a barrier the departed ones never reach. */
static volatile int g_phys_end;

/* Runs for secs seconds and returns, or forever if secs is 0. The frame
 * loop lives in here rather than in the caller because the particle state
 * only stays in registers if the function that declares it owns the loop.
 *
 */
void phys_scene(unsigned int secs) {
    const int t = tid();

    fx px[PPT], py[PPT], pz[PPT], vx[PPT], vy[PPT], vz[PPT];
    unsigned int col[PPT];

    for (int i = 0; i < PPT; i++) {
        int g = t * PPT + i;                    /* global particle index */
        unsigned int h = hash((unsigned int)g + 1);
        px[i] = FX_FRAC(((g % 11) - 5) * 5, 10);
        pz[i] = FX_FRAC((((g / 11) % 11) - 5) * 5, 10);
        py[i] = FX_FRAC(5 + (int)(h % 30), 10);
        vx[i] = FX_FRAC((int)((h >> 5) % 21) - 10, 700);
        vy[i] = 0;
        vz[i] = FX_FRAC((int)((h >> 13) % 21) - 10, 700);
        col[i] = part_colour(g);
    }

    unsigned int next = TIMER_US + FRAME_US;
    unsigned int end  = TIMER_US + secs * 1000000u;
    for (int f = 0; ; f++) {
        angle_t a = (angle_t)(f * 120);
        camera_t cam;
        cam_init(&cam, SCREEN_W, SCREEN_H);
        cam.pos = v3(fx_mul(FX(ORBIT_R), fx_sin(a)), FX(3),
                     fx_mul(FX(ORBIT_R), fx_cos(a)));
        cam_look_at(&cam, v3(0, FX(1), 0));

        mat4 vp;
        cam_viewproj(&cam, &vp);

        draw_background();
        draw_box(&vp);

        /* Uniform trip count, so the loop itself never diverges -- only the
         * collision responses inside it do. */
        for (int i = 0; i < PPT; i++) {
            vy[i] += GRAVITY;
            px[i] += vx[i]; py[i] += vy[i]; pz[i] += vz[i];

            MASKED(ballot(py[i] < FLOOR)) { PMOV(py[i], FLOOR); PMOV(vy[i], -fx_mul(vy[i], REST_F)); }
            MASKED(ballot(py[i] > CEIL))  { PMOV(py[i], CEIL);  PMOV(vy[i], -fx_mul(vy[i], REST_W)); }
            MASKED(ballot(px[i] < -WALL)) { PMOV(px[i], -WALL); PMOV(vx[i], -fx_mul(vx[i], REST_W)); }
            MASKED(ballot(px[i] >  WALL)) { PMOV(px[i],  WALL); PMOV(vx[i], -fx_mul(vx[i], REST_W)); }
            MASKED(ballot(pz[i] < -WALL)) { PMOV(pz[i], -WALL); PMOV(vz[i], -fx_mul(vz[i], REST_W)); }
            MASKED(ballot(pz[i] >  WALL)) { PMOV(pz[i],  WALL); PMOV(vz[i], -fx_mul(vz[i], REST_W)); }

            int dead = (py[i] < FLOOR + FX_FRAC(6,100)) && (fx_abs(vy[i]) < FX_FRAC(3,100));
            MASKED(ballot(dead)) { PMOV(py[i], FX_FRAC(35, 10)); PMOV(vy[i], FX_FRAC(0, 1)); }

            int sx, sy; fx iw = 0;
            int vis = project(&vp, v3(px[i], py[i], pz[i]), &sx, &sy, &iw);
            fx kb = fx_clamp(fx_mul(iw, FX(9)), FX_FRAC(35,100), FX_ONE);
            unsigned int cc = shade(col[i], kb);

            MASKED(ballot(vis)) {
                put(sx, sy, cc);
                put(sx + 1, sy, cc);
                put(sx, sy + 1, cc);
                put(sx + 1, sy + 1, cc);
            }
        }

        /* Every warp scatters particles across every row, so the buffer is
         * only whole once all four have arrived -- present cannot start early
         * the way it can in the rasteriser, where warps own their rows. */
        barrier(NWARPS_P);
        raster_present();

        /* Paced in warp 0 only. The spin is pure ALU and this scheduler only
         * switches warps on a memory stall, a barrier or terminate -- so four
         * warps spinning here would each hold the pipeline for their whole
         * slice. The other three block in the barrier below instead, which
         * yields properly and releases them the moment warp 0 arrives.
         *
         * Signed compare so the 32-bit timer wrap (~72 min) is harmless;
         * resync rather than sprint if a frame overran. */
        if (warpid() == 0) {
            if ((int)(TIMER_US - next) > 0) next = TIMER_US;
            else while ((int)(TIMER_US - next) < 0) { }
            next += FRAME_US;
            g_phys_end = secs && ((int)(TIMER_US - end) >= 0);
        }
        /* Also keeps the next frame's background from overwriting the buffer
         * while a slower warp is still blitting it, and publishes the
         * scene-end decision warp 0 just made. */
        barrier(NWARPS_P);
        if (g_phys_end) return;
    }
}

#ifndef DEMO_COMBINED
int main(void) {
    if (warpid() == 0) wspawn(NWARPS_P, (void*)0);
    phys_scene(0);
    return 0;
}
#endif
