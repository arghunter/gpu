#include "gpu.h"
#include "camera.h"
#include "raster.h"

/* SPH fluid, Clavet-style double density relaxation.
 *
 * NEIGHBOUR SEARCH IS ALL-PAIRS, deliberately. A spatial hash needs atomics
 * to bin particles and this machine has none, and walking a sorted neighbour
 * list is a divergent gather -- which this LSU bills at one transaction per
 * lane, so 16x. Brute force avoids both: the neighbour index j is
 * warp-uniform, so reading particle j is a broadcast, and the loop over j is
 * the same length for every lane. O(N^2) arithmetic is the cheap resource
 * here; memory divergence is the expensive one.
 *
 * NO SQRT AND NO DIVIDE IN THE INNER LOOP. fx_div is a 64-bit divide, which
 * on rv32im is a call to __udivdi3 -- unaffordable N^2 times. So the
 * smoothing radius is fixed at h = 1 and every kernel is written as a
 * polynomial in u = r^2 directly, never in r. The displacement uses the
 * kernel GRADIENT, which carries the separation vector d as a factor and so
 * needs no normalisation:
 *
 *     W(u) = (1-u)^k   =>   grad_i W  proportional to  (1-u)^(k-1) * d
 *
 * NO BRANCHES IN THE INNER LOOP EITHER. A branch on a per-lane value is
 * resolved from the active lane's register, so lanes that disagree get the
 * wrong answer silently. The cutoff at the smoothing radius is therefore
 * arithmetic: (1-u) is negated to a 0/-1 mask and ANDed, which clamps the
 * weight to zero outside the radius with no control flow at all. That also
 * makes the self-pair harmless -- d is zero, so it contributes nothing to the
 * force, and its fixed contribution to density just shifts RHO0. */

#ifndef NWARPS_F
#define NWARPS_F 4
#endif
_Static_assert(NWARPS_F == NWARPS_R, "scene warp counts must match");

/* Particles per thread. Measured on this machine (lsubench): a broadcast
 * load is ~26 cycles, an fx_mul ~22, and a SCATTERED load -- which is what a
 * stack spill is, one cache line per lane -- is ~168. Spilling anything into
 * an N^2 loop therefore costs more than the loop's arithmetic. Hence the
 * sweep below is written one own-particle at a time with scalar accumulators:
 * it gives up re-using a neighbour across several of this thread's particles,
 * but the working set is small enough that nothing spills, and 168-cycle
 * spills cost far more than the 26-cycle reloads they would have saved. */
#ifndef PPT_F
#define PPT_F 8
#endif
#define NTHREAD_F (NWARPS_F * NLANES)
#define NPART_F   (NTHREAD_F * PPT_F)

#ifndef TARGET_FPS
#define TARGET_FPS 60
#endif
#define FRAME_US (1000000u / TARGET_FPS)

/* Tank is deliberately tighter than the physics demo's. At h = 1 the
 * smoothing radius has to span several particle spacings or the density
 * estimate is noise, and 256 particles only reach that in a small volume. */
#define WALL_F  FX_FRAC(18, 10)
#define FLOOR_F FX_FRAC(-24, 10)
#define CEIL_F  FX_FRAC(24, 10)

/* Tuned on a host mirror of this exact fixed-point loop rather than in
 * simulation -- each Verilator run is ~4 minutes, so a sweep here would have
 * cost hours. RHO0 sets how far the pool expands: too high and the pressure
 * term is net negative at equilibrium, which pulls the fluid into a dead blob
 * on the floor instead of a pool with volume. */
#define RHO0    FX(6)                 /* rest density, in kernel units */
#define K_P     FX_FRAC(6, 1000)      /* pressure stiffness */
#define K_N     FX_FRAC(6, 1000)      /* near-pressure: resists clumping */
#define GRAV_F  FX_FRAC(-4, 1000)
#define DAMP_F  FX_FRAC(997, 1000)

/* Left to itself this settles in about five seconds and then sits perfectly
 * still -- position-based relaxation is very dissipative. A slowly reversing
 * horizontal gravity keeps it sloshing, which reads as the tank being tilted
 * back and forth and is what actually makes it look like liquid. */
#define SLOSH_A FX_FRAC(25, 10000)
#define SLOSH_P 170                   /* frames per full cycle */
#define VMAX    FX_FRAC(12, 100)      /* backstop: fixed point cannot recover
                                       * from a blow-up, so cap rather than
                                       * trust the pressure term */
/* Tank is half the width of the physics demo's, so the camera has to come
 * in proportionally or the fluid is a smudge in the middle of the frame. */
#define ORBIT_RF FX(6)

#define NOINIT __attribute__((section(".noinit")))

/* Laid out so slot i of thread t is at i*NTHREAD_F + t: the threads of a warp
 * then hold consecutive addresses for their own particles, and the sweep over
 * j walks the array linearly as a broadcast. */
/* Shared positions are Q8.8, not Q16.16. That makes the separation vector
 * Q8.8, so r^2 = dx*dx+dy*dy+dz*dz is a plain 32-bit multiply landing
 * directly in Q16.16 -- one `mul` instead of fx_mul's mul+mulh+shift, on the
 * three multiplies that every pair in the N^2 sweep pays. The displacement
 * c*d folds the same way. At 1/256 the position resolution is 0.004 against a
 * particle spacing of ~0.5; checked against a Q16.16 reference over 600
 * frames, the settled density and velocity are indistinguishable.
 * Each thread keeps its OWN positions at full Q16.16 in registers -- only the
 * shared copy others read is narrowed. */
static int f_qx[NPART_F] NOINIT, f_qy[NPART_F] NOINIT, f_qz[NPART_F] NOINIT;
static fx f_rho[NPART_F] NOINIT, f_rhon[NPART_F] NOINIT;

#define BB raster_fb

static inline void put(int x, int y, unsigned int c) {
    int ok  = ((unsigned)x < SCREEN_W) && ((unsigned)y < SCREEN_H);
    int idx = ok ? (y * SCREEN_W + x) : 0;
    MASKED(ballot(ok)) { BB[idx] = c; }
}

static void draw_background(void) {
    const int lane = laneid();
    const int warp = warpid() & (NWARPS_F - 1);
    for (int y = warp; y < SCREEN_H; y += NWARPS_F) {
        unsigned int k = (unsigned int)y;
        unsigned int r = 2 + (k * 10) / SCREEN_H;
        unsigned int g = 3 + (k * 16) / SCREEN_H;
        unsigned int b = 9 + (k * 32) / SCREEN_H;
        int base = y * SCREEN_W;
        for (int x = lane; x < SCREEN_W; x += NLANES) {
            unsigned int d = (unsigned int)(((x & 1) << 3) | ((y & 1) << 2)
                                          |  (x & 2)       | ((y & 2) >> 1));
            BB[base + x] = ((r + d) << 16) | ((g + d) << 8) | (b + d);
        }
    }
}

#define SEG_SAMP  16
#define N_BOX_E   12
#define N_GRID    12
#define N_SEG     (N_BOX_E + N_GRID)

static const signed char box_e[N_BOX_E][2] = {
    {0,1},{1,2},{2,3},{3,0},   {4,5},{5,6},{6,7},{7,4},   {0,4},{1,5},{2,6},{3,7},
};

static void corner(int i, vec3* o) {
    *o = v3((i == 1 || i == 2 || i == 5 || i == 6) ?  WALL_F : -WALL_F,
            (i < 4) ? FLOOR_F : CEIL_F,
            (i == 2 || i == 3 || i == 6 || i == 7) ?  WALL_F : -WALL_F);
}

static void segment(int s, vec3* a, vec3* b) {
    if (s < N_BOX_E) {
        corner(box_e[s][0], a);
        corner(box_e[s][1], b);
    } else {
        int g = s - N_BOX_E;
        int i = g % 6;
        fx u = -WALL_F + fx_mul(FX_FRAC(i, 5), WALL_F * 2);
        if (g < 6) { *a = v3(u, FLOOR_F, -WALL_F); *b = v3(u, FLOOR_F,  WALL_F); }
        else       { *a = v3(-WALL_F, FLOOR_F, u); *b = v3( WALL_F, FLOOR_F, u); }
    }
}

static unsigned int shade(unsigned int c, fx k) {
    unsigned int r = (c >> 16) & 0xFF, g = (c >> 8) & 0xFF, b = c & 0xFF;
    r = (unsigned int)(((long long)r * k) >> FX_SHIFT);
    g = (unsigned int)(((long long)g * k) >> FX_SHIFT);
    b = (unsigned int)(((long long)b * k) >> FX_SHIFT);
    return (r << 16) | (g << 8) | b;
}

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
    for (int k = tid(); k < N_SEG * SEG_SAMP; k += NTHREAD_F) {
        int s = k / SEG_SAMP, i = k % SEG_SAMP;
        vec3 a, b;
        segment(s, &a, &b);
        vec3 p = v3_lerp(a, b, FX_FRAC(i, SEG_SAMP));
        int sx, sy; fx iw;
        int ok = project(vp, p, &sx, &sy, &iw);
        fx k2 = fx_clamp(fx_mul(iw, FX(9)), FX_FRAC(45,100), FX_ONE);
        unsigned int c = shade(s < N_BOX_E ? 0x80B8E0 : 0x386890, k2);
        MASKED(ballot(ok)) { put(sx, sy, c); }
    }
}

/* Deep blue at rest, white where it is moving fast -- the single cue that
 * reads as water rather than as drifting points. */
static unsigned int speed_colour(fx s2) {
    fx k = fx_clamp(fx_mul(s2, FX(90)), 0, FX_ONE);
    unsigned int r = 0x18 + (unsigned int)((0xE0 * k) >> FX_SHIFT);
    unsigned int g = 0x48 + (unsigned int)((0xB0 * k) >> FX_SHIFT);
    unsigned int b = 0xC8 + (unsigned int)((0x37 * k) >> FX_SHIFT);
    return (r << 16) | (g << 8) | b;
}

static volatile int g_fluid_end;

void fluid_scene(unsigned int secs) {
    const int t = tid();

    fx px[PPT_F], py[PPT_F], pz[PPT_F], vx[PPT_F], vy[PPT_F], vz[PPT_F];

    /* Dropped as a block in the upper half of the tank, so the first seconds
     * show it collapse and slosh rather than start already settled. */
    for (int i = 0; i < PPT_F; i++) {
        int g = i * NTHREAD_F + t;
        px[i] = FX_FRAC(-12 + (g % 8) * 34, 100);
        py[i] = FX_FRAC(  2 + ((g / 8) % 8) * 25, 100);
        pz[i] = FX_FRAC(-12 + ((g / 64) % 8) * 34, 100);
        vx[i] = vy[i] = vz[i] = 0;
    }

    unsigned int next = TIMER_US + FRAME_US;
    unsigned int end  = TIMER_US + secs * 1000000u;

    for (int f = 0; ; f++) {
#ifdef FLUID_STATS
        unsigned int t0 = TIMER_US;
#endif
        /* Predict: gravity, then advance by the velocity. Relaxation below
         * corrects the position and the velocity is read back from how far
         * the particle actually moved -- position-based, which is far more
         * forgiving in fixed point than integrating a stiff pressure force. */
        fx ox[PPT_F], oy[PPT_F], oz[PPT_F];
        fx gx = fx_mul(SLOSH_A, fx_sin((angle_t)(f * (65536 / SLOSH_P))));
        for (int i = 0; i < PPT_F; i++) {
            vy[i] += GRAV_F;
            vx[i] += gx;
            vx[i] = fx_mul(vx[i], DAMP_F);
            vy[i] = fx_mul(vy[i], DAMP_F);
            vz[i] = fx_mul(vz[i], DAMP_F);
            ox[i] = px[i]; oy[i] = py[i]; oz[i] = pz[i];
            px[i] += vx[i]; py[i] += vy[i]; pz[i] += vz[i];
            int g = i * NTHREAD_F + t;
            f_qx[g] = px[i] >> 8; f_qy[g] = py[i] >> 8; f_qz[g] = pz[i] >> 8;
        }
        barrier(NWARPS_F);

        /* Pass 1 -- density and near-density. */
        for (int i = 0; i < PPT_F; i++) {
            const int cx8 = px[i] >> 8, cy8 = py[i] >> 8, cz8 = pz[i] >> 8;
            fx r = 0, rn = 0;
            for (int j = 0; j < NPART_F; j++) {
                int dx = f_qx[j] - cx8, dy = f_qy[j] - cy8, dz = f_qz[j] - cz8;
                fx u = dx*dx + dy*dy + dz*dz;
                fx w = FX_ONE - u;
                w &= -(w > 0);                  /* radius cutoff, branchless */
                fx w2 = fx_mul(w, w);
                r  += w2;
                rn += fx_mul(w2, w);
            }
            int g = i * NTHREAD_F + t;
            /* Stored as pressure, not density: the conversion is per particle
             * and would otherwise be repeated N times inside pass 2. */
            f_rho[g]  = fx_mul(r - RHO0, K_P);
            f_rhon[g] = fx_mul(rn, K_N);
        }
        barrier(NWARPS_F);

        /* Pass 2 -- displacement. Each particle applies the whole pair
         * displacement to itself; particle j does the same with d reversed,
         * so the pair still moves apart symmetrically and nothing is ever
         * written to another thread's slot. That is what removes the need for
         * atomics, which this hardware does not have. Using the AVERAGED
         * pressure of the pair keeps the two halves equal and opposite, so
         * momentum is conserved exactly. */
        for (int i = 0; i < PPT_F; i++) {
            int g = i * NTHREAD_F + t;
            const fx pr = f_rho[g], pn = f_rhon[g];
            const int cx8 = px[i] >> 8, cy8 = py[i] >> 8, cz8 = pz[i] >> 8;
            fx cx = px[i], cy = py[i], cz = pz[i];
            for (int j = 0; j < NPART_F; j++) {
                int dx = f_qx[j] - cx8, dy = f_qy[j] - cy8, dz = f_qz[j] - cz8;
                fx u = dx*dx + dy*dy + dz*dz;
                fx w = FX_ONE - u;
                w &= -(w > 0);
                /* (P_i+P_j)/2 * (1-u)  +  (Pn_i+Pn_j)/2 * (1-u)^2 */
                fx c = fx_mul((pr + f_rho[j]) >> 1, w)
                     + fx_mul((pn + f_rhon[j]) >> 1, fx_mul(w, w));
                /* c is Q16.16 and d is Q8.8, so the product is Q24.24 and a
                 * shift of 8 lands back in Q16.16 -- a plain mul again. */
                cx -= (c * dx) >> 8;
                cy -= (c * dy) >> 8;
                cz -= (c * dz) >> 8;
            }
            px[i] = cx; py[i] = cy; pz[i] = cz;
        }

        /* Walls, then velocity from the actual displacement. */
        camera_t cam;
        cam_init(&cam, SCREEN_W, SCREEN_H);
        angle_t a = (angle_t)(f * 90);
        cam.pos = v3(fx_mul(ORBIT_RF, fx_sin(a)), FX_FRAC(16, 10),
                     fx_mul(ORBIT_RF, fx_cos(a)));
        cam_look_at(&cam, v3(0, 0, 0));
        mat4 vp;
        cam_viewproj(&cam, &vp);

        draw_background();
        draw_box(&vp);

        for (int i = 0; i < PPT_F; i++) {
            MASKED(ballot(py[i] < FLOOR_F)) { PMOV(py[i], FLOOR_F); }
            MASKED(ballot(py[i] > CEIL_F))  { PMOV(py[i], CEIL_F); }
            MASKED(ballot(px[i] < -WALL_F)) { PMOV(px[i], -WALL_F); }
            MASKED(ballot(px[i] >  WALL_F)) { PMOV(px[i],  WALL_F); }
            MASKED(ballot(pz[i] < -WALL_F)) { PMOV(pz[i], -WALL_F); }
            MASKED(ballot(pz[i] >  WALL_F)) { PMOV(pz[i],  WALL_F); }

            vx[i] = fx_clamp(px[i] - ox[i], -VMAX, VMAX);
            vy[i] = fx_clamp(py[i] - oy[i], -VMAX, VMAX);
            vz[i] = fx_clamp(pz[i] - oz[i], -VMAX, VMAX);

            fx s2 = fx_mul(vx[i],vx[i]) + fx_mul(vy[i],vy[i]) + fx_mul(vz[i],vz[i]);
            unsigned int cc = speed_colour(s2);

            int sx, sy; fx iw = 0;
            int vis = project(&vp, v3(px[i], py[i], pz[i]), &sx, &sy, &iw);
            /* 3x3 rather than 2x2: at 192 particles the individual dots read
             * as dust, and overlapping blobs are what make it look like a
             * connected body of liquid. Nine stores per particle is nothing
             * against the N^2 sweep. */
            MASKED(ballot(vis)) {
                for (int dy = -1; dy <= 1; dy++)
                    for (int dx = -1; dx <= 1; dx++)
                        put(sx + dx, sy + dy, cc);
            }
        }

        barrier(NWARPS_F);
        raster_present();

#ifdef FLUID_STATS
        unsigned int tf = TIMER_US - t0;
#endif
        if (warpid() == 0) {
            if ((int)(TIMER_US - next) > 0) next = TIMER_US;
            else while ((int)(TIMER_US - next) < 0) { }
#ifdef FLUID_STATS
            if ((f & 31) == 0) say("fluid ", tf);
#endif
            next += FRAME_US;
            g_fluid_end = secs && ((int)(TIMER_US - end) >= 0);
        }
        barrier(NWARPS_F);
        if (g_fluid_end) return;
    }
}

#ifndef DEMO_COMBINED
int main(void) {
    if (warpid() == 0) wspawn(NWARPS_F, (void*)0);
    fluid_scene(0);
    return 0;
}
#endif
