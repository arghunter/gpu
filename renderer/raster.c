#include "raster.h"
#include "gpu.h"

#ifdef GPU_HOST
#define NOINIT
#else
#define NOINIT __attribute__((section(".noinit")))
#endif

zfx raster_zbuf[SCREEN_W * SCREEN_H] NOINIT;
unsigned int raster_fb[SCREEN_W * SCREEN_H] NOINIT;

/* FNV-style rolling hash of the depth buffer. One line of output instead of
 * thousands, and it separates a depth divergence from a colour-write one. */
unsigned int raster_zsum(void) {
    unsigned int h = 2166136261u;
    for (int i = 0; i < SCREEN_W * SCREEN_H; i++) {
        h ^= (unsigned int)raster_zbuf[i];
        h *= 16777619u;
    }
    return h;
}

/* Strided by lane so each store instruction covers NLANES distinct pixels.
 *
 * Written scalar this is the single most expensive thing in the frame: the
 * LSU issues one transaction per active lane regardless, so a scalar store
 * spends 16 transactions writing one pixel 16 times. Striding turns the same
 * 16 transactions into 16 pixels. SCREEN_W*SCREEN_H is a multiple of NLANES,
 * so the trip count stays warp-uniform and no masking is needed. */
void raster_present(void) {
    const int lane = laneid();
    const int warp = warpid() & (NWARPS_R - 1);
    for (int y = warp; y < SCREEN_H; y += NWARPS_R) {
        int base = y * SCREEN_W;
        for (int x = lane; x < SCREEN_W; x += NLANES)
            FB[base + x] = raster_fb[base + x];
    }
}

void raster_clear(unsigned int color) {
    const int lane = laneid();
    const int warp = warpid() & (NWARPS_R - 1);
    /* Partitioned by ROW, matching raster_tri. Splitting the clear by linear
     * index instead would have a warp clearing rows another warp is about to
     * draw into. */
    for (int y = warp; y < SCREEN_H; y += NWARPS_R) {
        int base = y * SCREEN_W;
        for (int x = lane; x < SCREEN_W; x += NLANES) {
            raster_fb[base + x] = color;
            raster_zbuf[base + x] = 0;  /* 0 == infinitely far: we keep the
                                         * LARGEST 1/w */
        }
    }
}

/* Edge function for the directed edge a->b evaluated at p, all Q28.4.
 *
 * Computed in 64 bits and returned as int: inside the guard band the true
 * value is under 1.4e9, and geom_to_screen rejects anything outside it, so
 * the narrowing is safe. The 64-bit intermediate is still required -- the
 * operands alone reach 2e5 * 3e4. */
static inline int edge(int ax, int ay, int bx, int by, int px, int py) {
    return (int)(((long long)(bx - ax) * (py - ay)) -
                 ((long long)(by - ay) * (px - ax)));
}

void raster_tri(const svert_t* a, const svert_t* b, const svert_t* c) {
    /* Front faces have negative area: world-space winding is CCW and
     * geom_to_screen flips Y. */
    long long area = ((long long)(b->x - a->x) * (c->y - a->y)) -
                     ((long long)(b->y - a->y) * (c->x - a->x));
    if (area >= -(long long)(SUBPIX_ONE * SUBPIX_ONE)) return;   /* back-facing or sliver */
    area = -area;                       /* work with a positive area below */

    int minx = a->x, maxx = a->x, miny = a->y, maxy = a->y;
    if (b->x < minx) minx = b->x;
    if (c->x < minx) minx = c->x;
    if (b->x > maxx) maxx = b->x;
    if (c->x > maxx) maxx = c->x;
    if (b->y < miny) miny = b->y;
    if (c->y < miny) miny = c->y;
    if (b->y > maxy) maxy = b->y;
    if (c->y > maxy) maxy = c->y;

    int x0 = minx >> SUBPIX, x1 = maxx >> SUBPIX;
    int y0 = miny >> SUBPIX, y1 = maxy >> SUBPIX;
    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 > SCREEN_W - 1) x1 = SCREEN_W - 1;
    if (y1 > SCREEN_H - 1) y1 = SCREEN_H - 1;
    if (x0 > x1 || y0 > y1) return;

    /* Per-pixel steps of the three edge functions. dE/dx = -(by-ay) and
     * dE/dy = (bx-ax), scaled by one whole pixel. */
    int dx0 =  (c->y - b->y) * SUBPIX_ONE, dy0 = -(c->x - b->x) * SUBPIX_ONE;
    int dx1 =  (a->y - c->y) * SUBPIX_ONE, dy1 = -(a->x - c->x) * SUBPIX_ONE;
    int dx2 =  (b->y - a->y) * SUBPIX_ONE, dy2 = -(b->x - a->x) * SUBPIX_ONE;

    /* Sample at pixel centres, half a pixel in from the corner. */
    int px = (x0 << SUBPIX) + SUBPIX_ONE / 2;
    int py = (y0 << SUBPIX) + SUBPIX_ONE / 2;

    /* Negated along with the area, so "inside" is all three >= 0. The ratio
     * zn/area is unaffected because numerator and denominator flip together,
     * and the sign convention lets the coverage test collapse to a single
     * OR -- which is exactly the form M2 needs for ballot(). */
    int row0 = -edge(b->x, b->y, c->x, c->y, px, py);
    int row1 = -edge(c->x, c->y, a->x, a->y, px, py);
    int row2 = -edge(a->x, a->y, b->x, b->y, px, py);

    /* 1/w is linear in screen space, so it is a plane through the three
     * vertex values, weighted by the unnormalised edge functions. Dividing
     * the plane terms by the area ONCE turns per-pixel depth into an integer
     * add -- M1 divided a 64-bit numerator by the area at every covered
     * pixel, which on RV32 is a __divdi3 call per pixel. The truncation costs
     * a few counts of Q2.30 across a whole triangle, far under its
     * resolution. */
    long long zn_row = (long long)row0 * a->invw +
                       (long long)row1 * b->invw +
                       (long long)row2 * c->invw;
    long long zdx = (long long)dx0 * a->invw + (long long)dx1 * b->invw + (long long)dx2 * c->invw;
    long long zdy = (long long)dy0 * a->invw + (long long)dy1 * b->invw + (long long)dy2 * c->invw;

    int za    = (int)(zdx / area);
    int zb    = (int)(zdy / area);
    int z_row = (int)(zn_row / area);


#ifdef DUMP_RAST
    MASKED(1) {
        putc_('R'); putc_(' '); hex_((unsigned)(int)area);
        putc_(' '); hex_((unsigned)za); putc_(' '); hex_((unsigned)zb);
        putc_(' '); hex_((unsigned)z_row);
        putc_(' '); hex_((unsigned)x0); putc_(' '); hex_((unsigned)x1);
        putc_(' '); hex_((unsigned)y0); putc_(' '); hex_((unsigned)y1);
        putc_('\n');
    }
#endif
    unsigned int col = a->col;

    /* Advance to this warp's first owned row at or after y0, then step whole
     * warp-strides. The edge and depth accumulators are seeded the same
     * number of rows forward. */
    const int warp = warpid() & (NWARPS_R - 1);
    int ystart = y0 + ((warp - y0) & (NWARPS_R - 1));
    if (ystart > y1) return;
    {
        int yoff = ystart - y0;
        row0 += dy0 * yoff; row1 += dy1 * yoff; row2 += dy2 * yoff;
        z_row += zb * yoff;
    }

    /* Lanes cover NLANES horizontally adjacent pixels. Each lane carries its
     * own edge and depth accumulators, seeded at its own column and advanced
     * a whole block at a time. */
    const int lane = laneid();
    row0 += dx0 * lane; row1 += dx1 * lane; row2 += dx2 * lane;
    z_row += za * lane;

    const int bx0 = dx0 * NLANES, bx1 = dx1 * NLANES, bx2 = dx2 * NLANES;
    const int bz  = za * NLANES;

    for (int y = ystart; y <= y1; y += NWARPS_R) {
        int e0 = row0, e1 = row1, e2 = row2, z = z_row;
        int base = y * SCREEN_W;

        for (int xb = x0; xb <= x1; xb += NLANES) {
            int x = xb + lane;

            /* Inside means no sign bit set in any edge function. The x bound
             * matters on the final block, where lanes run past the bbox. */
            int cov = (x <= x1) && ((e0 | e1 | e2) >= 0);

            /* Clamped so every lane's address is in range, which lets the
             * depth load run UNMASKED. That matters: gpu.h's rule is that
             * only stores are safe inside a masked block, because GCC models
             * a masked write as a full one and allocates registers
             * accordingly. A masked load -- and worse, a second mask nested
             * inside the first -- puts many live variables across a mask
             * change, and the result is allocation-dependent: it moves or
             * vanishes with any instrumentation. Loading unmasked and masking
             * only the two stores keeps the whole loop inside the rule. */
            /* Skip blocks no lane touches. ballot is warp-uniform so the
             * branch is safe, and without it every block outside the triangle
             * still issues NLANES depth loads -- for a full-screen clipped
             * triangle that is ~77k wasted transactions. */
            if (ballot(cov)) {
                int sx = (x <= x1) ? x : x1;
                int idx = base + sx;
                zfx old = raster_zbuf[idx];

                MASKED(ballot(cov && z > old)) {
                    raster_zbuf[idx] = z;
                    raster_fb[idx] = col;
                }
            }

            e0 += bx0; e1 += bx1; e2 += bx2; z += bz;
        }
        row0 += dy0 * NWARPS_R; row1 += dy1 * NWARPS_R;
        row2 += dy2 * NWARPS_R; z_row += zb * NWARPS_R;
    }
}
