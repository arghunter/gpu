#include "geom.h"
#include "gpu.h"

/* Signed distance to the near plane in clip space. The projection maps the
 * near plane to ndc.z == -1, i.e. clip.z == -clip.w, so this is positive in
 * front of it. Clipping here rather than after the divide is what keeps
 * vertices at or behind the eye from producing infinities. */
static inline fx near_dist(vec4 v) { return v.z + v.w; }

static inline vec4 lerp4(vec4 a, vec4 b, fx t) {
    return v4(a.x + fx_mul(b.x - a.x, t),
              a.y + fx_mul(b.y - a.y, t),
              a.z + fx_mul(b.z - a.z, t),
              a.w + fx_mul(b.w - a.w, t));
}

int geom_clip_near(const vec4 in[3], vec4 out[6]) {
    fx   d[3];
    int  inside[3], nin = 0;
    for (int i = 0; i < 3; i++) {
        d[i] = near_dist(in[i]);
        inside[i] = d[i] >= 0;
        nin += inside[i];
    }
    if (nin == 0) return 0;
    if (nin == 3) { out[0] = in[0]; out[1] = in[1]; out[2] = in[2]; return 1; }

    /* Walk the edges and emit the clipped polygon. Winding is preserved
     * because vertices are appended in edge order, which matters: the
     * rasteriser culls on the sign of the area. */
    vec4 poly[4];
    int  n = 0;
    for (int i = 0; i < 3; i++) {
        int j = (i + 1) % 3;
        if (inside[i]) poly[n++] = in[i];
        if (inside[i] != inside[j]) {
            fx denom = d[i] - d[j];
            fx t = denom ? fx_div(d[i], denom) : 0;
            poly[n++] = lerp4(in[i], in[j], t);
        }
    }
    if (n < 3) return 0;
    out[0] = poly[0]; out[1] = poly[1]; out[2] = poly[2];
    if (n == 3) return 1;
    out[3] = poly[0]; out[4] = poly[2]; out[5] = poly[3];
    return 2;
}

int geom_to_screen(vec4 clip, unsigned int col, svert_t* out) {
    if (clip.w <= 0) return 0;

    fx iw = fx_div(FX_ONE, clip.w);
    fx nx = fx_mul(clip.x, iw);
    fx ny = fx_mul(clip.y, iw);

    /* ndc [-1,1] -> pixels, then to Q28.4. Y is flipped because screen rows
     * grow downward; that flip reverses triangle winding, which is why the
     * rasteriser culls on negative area. */
    long long px = ((long long)(nx + FX_ONE) * (SCREEN_W * SUBPIX_ONE / 2)) >> FX_SHIFT;
    long long py = ((long long)(FX_ONE - ny) * (SCREEN_H * SUBPIX_ONE / 2)) >> FX_SHIFT;

    if (px < -GUARD_SUB || px > (SCREEN_W * SUBPIX_ONE) + GUARD_SUB) return 0;
    if (py < -GUARD_SUB || py > (SCREEN_H * SUBPIX_ONE) + GUARD_SUB) return 0;

#ifdef DUMP_PROJ
    { static int n = 0;
      if (n < 3) { n++;
        MASKED(1) {
            putc_('G');
            putc_(' '); hex_((unsigned)clip.x);
            putc_(' '); hex_((unsigned)clip.w);
            putc_(' '); hex_((unsigned)iw);
            putc_(' '); hex_((unsigned)nx);
            putc_(' '); hex_((unsigned)ny);
            putc_(' '); hex_((unsigned)(int)px);
            putc_(' '); hex_((unsigned)(int)py);
            putc_('\n');
        }
      } }
#endif
    out->x = (int)px;
    out->y = (int)py;
    /* invw = 1/w in Q2.30. w is Q16.16, so the numerator is 2^(30+16). */
    out->invw = (zfx)(((long long)1 << (Z_SHIFT + FX_SHIFT)) / clip.w);
    out->col  = col;
    return 1;
}
