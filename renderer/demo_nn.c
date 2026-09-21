#include "gpu.h"
#include "camera.h"
#include "raster.h"

/* Neural network visualiser: a 2-8-8-1 MLP learning two interleaved spirals,
 * trained on the GPU while you watch the decision boundary form.
 *
 * WHY THIS SHAPE. The expensive half is the decision field -- every pixel is
 * an independent forward pass, which is the ideal case for this machine: each
 * lane takes a different pixel, and every lane reads the SAME weight at the
 * same moment, so the weight fetch is a uniform-address load. Measured at
 * ~26 cycles against ~168 for a scattered one (see lsubench), that is the
 * difference between this being affordable and not.
 *
 * WHY BATCH DESCENT AND NOT SGD. Threads cannot accumulate into a shared
 * gradient -- no atomics. So each thread takes one sample, writes its own
 * gradient to its own slot, and a reduction pass sums the columns. That makes
 * it batch-64 descent rather than per-sample SGD, which needed a 4x smaller
 * step to stay stable; both were checked against a host mirror of this exact
 * fixed-point arithmetic before any of it was run in simulation.
 *
 * Weights are plain Q16.16. A wider accumulator was the obvious precaution --
 * an update of lr*grad can quantise to zero at 1.5e-5 resolution -- but the
 * host mirror reaches 100% without one, so it is not here. */

#ifndef NWARPS_N
#define NWARPS_N 4
#endif
_Static_assert(NWARPS_N == NWARPS_R, "scene warp counts must match");
#define NTHREAD_N (NWARPS_N * NLANES)

#ifndef TARGET_FPS
#define TARGET_FPS 60
#endif
#define FRAME_US (1000000u / TARGET_FPS)

#define H      8
#define NW     (H*5 + H*H + 1)        /* 105 live weights */
#define NWPAD  (NTHREAD_N * 2)        /* 128: two per thread, exactly */
#define NS     256                    /* samples; 4 batches of NTHREAD_N */
#define LR_SH  8                      /* step = 2^-8, tuned on the host */
#ifndef BATCHES_PER_FRAME
#define BATCHES_PER_FRAME 4
#endif

#define W1_(k,i) nn_w[(k)*2 + (i)]
#define B1_(k)   nn_w[H*2 + (k)]
#define W2_(k,j) nn_w[H*3 + (k)*H + (j)]
#define B2_(k)   nn_w[H*3 + H*H + (k)]
#define W3_(k)   nn_w[H*4 + H*H + (k)]
#define B3_      nn_w[H*5 + H*H]

#define NOINIT __attribute__((section(".noinit")))

static fx nn_w[NWPAD] NOINIT;
/* Gradient slot for weight w, thread t. Thread-minor so that when all lanes
 * write weight w at once the addresses are consecutive rather than a cache
 * line apart. */
static fx nn_g[NWPAD * NTHREAD_N] NOINIT;
static fx s_x[NS] NOINIT, s_y[NS] NOINIT;
static int s_l[NS] NOINIT;

/* Decision field is evaluated at 64x48 and upscaled 5x. A full-resolution
 * field would be 25x the forward passes for a boundary that is smooth enough
 * that nobody can tell. */
#define FW 64
#define FH 48
#define FSC 5
static unsigned int field[FW * FH] NOINIT;

#define BB raster_fb

static unsigned int hash(unsigned int x) {
    x ^= x << 13; x ^= x >> 17; x ^= x << 5; return x;
}

static inline void put(int x, int y, unsigned int c) {
    int ok  = ((unsigned)x < SCREEN_W) && ((unsigned)y < SCREEN_H);
    int idx = ok ? (y * SCREEN_W + x) : 0;
    MASKED(ballot(ok)) { BB[idx] = c; }
}

static inline fx relu(fx v) { return v & -(v > 0); }

/* Forward only. h2 is consumed as it is produced and never stored, which
 * keeps the live set to h1 plus an accumulator -- small enough that nothing
 * spills, and a spill inside the per-pixel loop would cost more than the
 * whole layer. */
static fx nn_eval(fx x, fx y) {
    fx h1[H];
    for (int k = 0; k < H; k++)
        h1[k] = relu(fx_mul(W1_(k,0), x) + fx_mul(W1_(k,1), y) + B1_(k));
    fx o = B3_;
    for (int k = 0; k < H; k++) {
        fx a = B2_(k);
        for (int j = 0; j < H; j++) a += fx_mul(W2_(k,j), h1[j]);
        o += fx_mul(W3_(k), relu(a));
    }
    return o;
}

static void make_data(int t) {
    for (int i = t; i < NS; i += NTHREAD_N) {
        int arm = i & 1;
        /* tt sweeps 0.4 .. 3.6; radius is tt/3.6 and the angle is 2*tt, so
         * the two arms are the same spiral half a turn apart. */
        fx tt = FX_FRAC(4, 10) + fx_mul(FX_FRAC(i >> 1, NS / 2), FX_FRAC(32, 10));
        angle_t a = (angle_t)(fx_mul(tt, FX(20860)) >> FX_SHIFT);
        if (arm) a = (angle_t)(a + 32768);          /* + pi */
        fx r = fx_mul(tt, FX_FRAC(10, 36));
        unsigned int hh = hash((unsigned int)i + 99);
        s_x[i] = fx_mul(r, fx_cos(a)) + FX_FRAC((int)(hh % 9) - 4, 100);
        s_y[i] = fx_mul(r, fx_sin(a)) + FX_FRAC((int)((hh >> 8) % 9) - 4, 100);
        s_l[i] = arm;
    }
}

static void init_weights(int t) {
    for (int w = t; w < NWPAD; w += NTHREAD_N) {
        unsigned int hh = hash((unsigned int)w * 2654435761u + 7);
        /* Second layer starts smaller: it has four times the fan-in, and an
         * over-large init there saturates every ReLU off at once. */
        int den = (w >= H*3) ? 2000 : 1000;
        nn_w[w] = (w < NW) ? FX_FRAC((int)(hh % 2001) - 1000, den) : 0;
    }
}

static void train_batch(int t, int base) {
    int i = base + t;
    fx x = s_x[i], y = s_y[i];
    fx h1[H], h2[H];

    for (int k = 0; k < H; k++)
        h1[k] = relu(fx_mul(W1_(k,0), x) + fx_mul(W1_(k,1), y) + B1_(k));
    fx o = B3_;
    for (int k = 0; k < H; k++) {
        fx a = B2_(k);
        for (int j = 0; j < H; j++) a += fx_mul(W2_(k,j), h1[j]);
        h2[k] = relu(a);
        o += fx_mul(W3_(k), h2[k]);
    }

    /* Targets are +-0.8 rather than +-1: a linear output chasing exactly 1
     * keeps growing the last layer's weights after the sign is already
     * right. */
    fx tgt = s_l[i] ? FX_FRAC(8,10) : -FX_FRAC(8,10);
    fx d3 = o - tgt;

    fx dh1[H];
    for (int j = 0; j < H; j++) dh1[j] = 0;

    for (int k = 0; k < H; k++) {
        nn_g[(H*4 + H*H + k) * NTHREAD_N + t] = fx_mul(d3, h2[k]);
        fx dp2 = fx_mul(d3, W3_(k)) & -(h2[k] > 0);
        for (int j = 0; j < H; j++) {
            dh1[j] += fx_mul(dp2, W2_(k,j));
            nn_g[(H*3 + k*H + j) * NTHREAD_N + t] = fx_mul(dp2, h1[j]);
        }
        nn_g[(H*3 + H*H + k) * NTHREAD_N + t] = dp2;
    }
    nn_g[(H*5 + H*H) * NTHREAD_N + t] = d3;

    for (int k = 0; k < H; k++) {
        fx dp1 = dh1[k] & -(h1[k] > 0);
        nn_g[(k*2 + 0) * NTHREAD_N + t] = fx_mul(dp1, x);
        nn_g[(k*2 + 1) * NTHREAD_N + t] = fx_mul(dp1, y);
        nn_g[(H*2 + k) * NTHREAD_N + t] = dp1;
    }
}

/* Sum each weight's column and apply. Exactly two weights per thread, so the
 * trip count is warp-uniform -- a `w < NW` bound would leave some lanes with
 * one iteration and some with two, and this machine resolves a branch from a
 * single lane's register. The padding entries past NW are summed and updated
 * too; nothing reads them. */
static void reduce_apply(int t) {
    for (int u = 0; u < 2; u++) {
        int w = u * NTHREAD_N + t;
        fx g = 0;
        for (int j = 0; j < NTHREAD_N; j++) g += nn_g[w * NTHREAD_N + j];
        nn_w[w] -= g >> LR_SH;
    }
}

static void draw_field(int t) {
    for (int p = t; p < FW * FH; p += NTHREAD_N) {
        int fxp = p % FW, fyp = p / FW;
        fx x = FX_FRAC(fxp - FW/2, FW/2);
        fx y = FX_FRAC(FH/2 - fyp, FH/2);
        fx o = nn_eval(x, y);
        /* Signed confidence -> two-sided ramp, so the boundary itself shows
         * as the dark seam where the output crosses zero. */
        fx m = fx_clamp(fx_abs(o), 0, FX_ONE);
        unsigned int s = (unsigned int)(m >> 11);           /* 0..31 */
        unsigned int r, g, b;
        /* Kept dark and well clear of 0xF0: the blit adds a dither offset to
         * the low bits afterwards, and a channel near full would carry into
         * the next one. */
        if (o > 0) { r = 0x22 + s*4; g = 0x18 + s*2; b = 0x14 + s;   }
        else       { r = 0x14 + s;   g = 0x1C + s*2; b = 0x26 + s*4; }
        field[p] = (r << 16) | (g << 8) | b;
    }
}

static void blit_field(void) {
    const int lane = laneid();
    const int warp = warpid() & (NWARPS_N - 1);
    for (int y = warp; y < SCREEN_H; y += NWARPS_N) {
        int frow = (y / FSC) * FW;
        int base = y * SCREEN_W;
        for (int x = lane; x < SCREEN_W; x += NLANES) {
            /* The VGA keeps only the top nibble of each channel, so the
             * confidence ramp would otherwise collapse into six flat bands.
             * Dithering here rather than in draw_field means it happens at
             * full 320x240 resolution instead of the field's 64x48. */
            unsigned int d = (unsigned int)(((x & 1) << 3) | ((y & 1) << 2)
                                          |  (x & 2)       | ((y & 2) >> 1));
            BB[base + x] = field[frow + x / FSC] + d * 0x010101u;
        }
    }
}

/* World (-1..1) to screen, matching draw_field's mapping. */
static inline void to_screen(fx x, fx y, int* sx, int* sy) {
    *sx = fx_round_int(fx_mul(x + FX_ONE, FX(SCREEN_W / 2)));
    *sy = fx_round_int(fx_mul(FX_ONE - y, FX(SCREEN_H / 2)));
}

static void draw_points(int t) {
    for (int i = t; i < NS; i += NTHREAD_N) {
        int sx, sy;
        to_screen(s_x[i], s_y[i], &sx, &sy);
        fx o = nn_eval(s_x[i], s_y[i]);
        int right = (o > 0) == (s_l[i] == 1);
        /* Misclassified points ring red, so the remaining errors are visible
         * individually once the boundary is nearly there. */
        unsigned int c = right ? (s_l[i] ? 0xFF9030 : 0x30C0FF) : 0xFF2020;
        for (int dy = -1; dy <= 1; dy++)
            for (int dx = -1; dx <= 1; dx++)
                put(sx + dx, sy + dy, (dx && dy) ? 0x101010 : c);
    }
}

/* Network diagram: four columns of nodes, every edge drawn with brightness
 * from its weight. 88 edges x 8 samples = 704 points, an exact multiple of
 * the thread count so the sampling loop stays warp-uniform. */
#define PANEL_X 6
#define PANEL_Y 6
#define PANEL_W 104
#define PANEL_H 92
#define ESAMP   8
#define NEDGE   (2*H + H*H + H)

static void node_pos(int layer, int i, int n, int* x, int* y) {
    *x = PANEL_X + 10 + layer * ((PANEL_W - 20) / 3);
    *y = PANEL_Y + 8 + (n > 1 ? (i * (PANEL_H - 16)) / (n - 1) : (PANEL_H - 16) / 2);
}

static void edge_ends(int e, int* x0, int* y0, int* x1, int* y1, fx* w) {
    if (e < 2*H)            { int k = e / 2,     i = e % 2;
        node_pos(0, i, 2, x0, y0);      node_pos(1, k, H, x1, y1); *w = W1_(k,i); }
    else if (e < 2*H + H*H) { int q = e - 2*H, k = q / H, j = q % H;
        node_pos(1, j, H, x0, y0);      node_pos(2, k, H, x1, y1); *w = W2_(k,j); }
    else                    { int k = e - 2*H - H*H;
        node_pos(2, k, H, x0, y0);      node_pos(3, 0, 1, x1, y1); *w = W3_(k); }
}

static void draw_net(int t) {
    /* Darken the panel so the diagram reads against the decision field. */
    const int lane = laneid();
    const int warp = warpid() & (NWARPS_N - 1);
    for (int y = PANEL_Y + warp; y < PANEL_Y + PANEL_H; y += NWARPS_N) {
        int base = y * SCREEN_W;
        for (int x = PANEL_X + lane; x < PANEL_X + PANEL_W; x += NLANES) {
            unsigned int c = BB[base + x];
            BB[base + x] = ((c >> 2) & 0x3F3F3F) + 0x080810;
        }
    }

    for (int k = t; k < NEDGE * ESAMP; k += NTHREAD_N) {
        int e = k / ESAMP, i = k % ESAMP;
        int x0, y0, x1, y1; fx w;
        edge_ends(e, &x0, &y0, &x1, &y1, &w);
        fx u = FX_FRAC(i, ESAMP);
        int px = x0 + (int)(((x1 - x0) * (long long)u) >> FX_SHIFT);
        int py = y0 + (int)(((y1 - y0) * (long long)u) >> FX_SHIFT);
        /* Excitatory warm, inhibitory cool, brightness by magnitude. */
        fx m = fx_clamp(fx_abs(w), 0, FX_ONE);
        unsigned int s = 0x20 + (unsigned int)((0xC0 * m) >> FX_SHIFT);
        put(px, py, w > 0 ? (s << 16) | ((s/2) << 8) | 0x20
                          : 0x20 << 16 | ((s/2) << 8) | s);
    }

    for (int k = t; k < (2 + H + H + 1) * 4; k += NTHREAD_N) {
        int n = k >> 2, d = k & 3;
        int layer = n < 2 ? 0 : (n < 2+H ? 1 : (n < 2+2*H ? 2 : 3));
        int idx   = n < 2 ? n : (n < 2+H ? n-2 : (n < 2+2*H ? n-2-H : 0));
        int cnt   = layer == 0 ? 2 : (layer == 3 ? 1 : H);
        int x, y; node_pos(layer, idx, cnt, &x, &y);
        put(x + (d & 1), y + (d >> 1), 0xF0F4FF);
    }
}

static volatile int g_nn_end;

void nn_scene(unsigned int secs) {
    const int t = tid();

    make_data(t);
    init_weights(t);
    barrier(NWARPS_N);

    unsigned int next = TIMER_US + FRAME_US;
    unsigned int end  = TIMER_US + secs * 1000000u;

    for (int f = 0; ; f++) {
#ifdef NN_STATS
        unsigned int t0 = TIMER_US;
#endif
        for (int b = 0; b < BATCHES_PER_FRAME; b++) {
            train_batch(t, ((f * BATCHES_PER_FRAME + b) % (NS / NTHREAD_N)) * NTHREAD_N);
            barrier(NWARPS_N);
            reduce_apply(t);
            barrier(NWARPS_N);
        }

        draw_field(t);
        barrier(NWARPS_N);
        blit_field();
        draw_points(t);
        draw_net(t);

        barrier(NWARPS_N);
        raster_present();

#ifdef NN_STATS
        unsigned int tf = TIMER_US - t0;
#endif
        if (warpid() == 0) {
            if ((int)(TIMER_US - next) > 0) next = TIMER_US;
            else while ((int)(TIMER_US - next) < 0) { }
#ifdef NN_STATS
            if ((f & 7) == 0) say("nn_us ", tf);
#endif
            next += FRAME_US;
            g_nn_end = secs && ((int)(TIMER_US - end) >= 0);
        }
        barrier(NWARPS_N);
        if (g_nn_end) return;
    }
}

#ifndef DEMO_COMBINED
int main(void) {
    if (warpid() == 0) wspawn(NWARPS_N, (void*)0);
    nn_scene(0);
    return 0;
}
#endif
