#include "gpu.h"
#include "camera.h"
#include "mesh.h"
#include "geom.h"
#include "raster.h"

/* M1: full pipeline at one lane -- near-plane clipping, Q28.4 subpixel
 * rasterisation, 1/w depth. Two interpenetrating cubes, because a single
 * convex solid renders correctly from backface culling alone and would not
 * prove the depth buffer does anything. */

#define V(x,y,z) { { FX(x), FX(y), FX(z) }, { 0,0,0 }, 0, 0 }
static const vertex_t cube_v[8] = {
    V(-1,-1,-1), V( 1,-1,-1), V( 1, 1,-1), V(-1, 1,-1),
    V(-1,-1, 1), V( 1,-1, 1), V( 1, 1, 1), V(-1, 1, 1),
};
static const unsigned short cube_i[36] = {
    0,2,1, 0,3,2,   4,5,6, 4,6,7,
    0,1,5, 0,5,4,   2,3,7, 2,7,6,
    1,2,6, 1,6,5,   0,4,7, 0,7,3,
};
static const mesh_t cube = { cube_v, cube_i, 8, 12 };

static void draw_mesh(const mesh_t* m, const mat4* mvp, const unsigned int* col) {
    int ntri_limit = m->ntris;
#ifdef MAXTRI
    if (ntri_limit > MAXTRI) ntri_limit = MAXTRI;
#endif
    for (int t = 0; t < ntri_limit; t++) {
        vec4 cl[3];
        for (int k = 0; k < 3; k++)
            cl[k] = mat4_mul_point(mvp, m->verts[m->idx[t * 3 + k]].pos);

#ifdef DUMP_CLIP
        MASKED(1) {
            putc_('C');
            for (int k = 0; k < 3; k++) {
                putc_(' '); hex_((unsigned)cl[k].x);
                putc_(' '); hex_((unsigned)cl[k].y);
                putc_(' '); hex_((unsigned)cl[k].z);
                putc_(' '); hex_((unsigned)cl[k].w);
            }
            putc_('\n');
        }
#endif
        vec4 poly[6];
        int ntri = geom_clip_near(cl, poly);
        for (int i = 0; i < ntri; i++) {
            svert_t sv[3];
            int ok = 1;
            for (int k = 0; k < 3; k++)
                ok &= geom_to_screen(poly[i * 3 + k], col[t], &sv[k]);
            if (ok) {
#ifdef DUMP_TRIS
                /* Same text from both targets, so a diff localises a
                 * divergence to the geometry stage or past it. */
                MASKED(1) {
                    putc_('T');
                    for (int q = 0; q < 3; q++) {
                        putc_(' '); hex_((unsigned)sv[q].x);
                        putc_(' '); hex_((unsigned)sv[q].y);
                        putc_(' '); hex_((unsigned)sv[q].invw);
                    }
                    putc_('\n');
                }
#endif
                raster_tri(&sv[0], &sv[1], &sv[2]);
#ifdef MASK_CHECK
                /* Force the mask full and capture what it actually was. This
                 * both detects a leak and repairs it, so one run lists every
                 * triangle that leaks instead of stopping at the first. */
                {
                    int mm = tmc(-1);
                    if (mm != (int)((1u << NLANES) - 1)) {
                        MASKED(1) {
                            putc_('!'); hex_((unsigned)t);
                            putc_(' '); hex_((unsigned)mm); putc_('\n');
                        }
                    }
                }
#endif
            }
        }
    }
}

static const unsigned int col_a[12] = {
    0xE04040,0xE04040, 0xC03030,0xC03030, 0xE06060,0xE06060,
    0xA02020,0xA02020, 0xF08080,0xF08080, 0x902020,0x902020,
};
static const unsigned int col_b[12] = {
    0x40A0E0,0x40A0E0, 0x3080C0,0x3080C0, 0x60C0E0,0x60C0E0,
    0x2060A0,0x2060A0, 0x80D0F0,0x80D0F0, 0x205090,0x205090,
};

void render_frame(int frame) {
    raster_clear(0x101018);
#ifdef CLEAR_ONLY
    return;
#endif

    camera_t cam;
    cam_init(&cam, SCREEN_W, SCREEN_H);
    /* Dolly in as the frame number rises, so high frames push the near plane
     * through the geometry and exercise geom_clip_near. Without this the
     * clipper never runs and a bug in it would sit undetected. */
    fx dist = FX(7) - FX_FRAC(frame, 8);
    if (dist < FX_FRAC(1, 2)) dist = FX_FRAC(1, 2);
    cam.pos = v3(FX(0), FX(2), dist);
    cam_look_at(&cam, v3(0, 0, 0));

    mat4 vp, rot, trn, model, mvp;
    cam_viewproj(&cam, &vp);
#ifdef DUMP_MAT
    MASKED(1) {
        mat4 pp; cam_proj(&cam, &pp);
        putc_('P');
        putc_(' '); hex_((unsigned)pp.m[0][0]);
        putc_(' '); hex_((unsigned)pp.m[1][1]);
        putc_(' '); hex_((unsigned)FX_FRAC(cam.vp_w, cam.vp_h));
        putc_(' '); hex_((unsigned)fx_sin((angle_t)(cam.fov/2)));
        putc_(' '); hex_((unsigned)fx_cos((angle_t)(cam.fov/2)));
        putc_(' '); hex_((unsigned)cam.fov);
        putc_('\n');
        putc_('V');
        for (int r = 0; r < 2; r++) for (int c2 = 0; c2 < 4; c2++) { putc_(' '); hex_((unsigned)vp.m[r][c2]); }
        putc_('\n');
    }
#endif

    /* The two cubes overlap by design: the seam where they intersect is the
     * depth buffer's signature, and it is wrong in an obvious way if 1/w
     * interpolation or the compare is broken. */
    mat4_rot_y(&rot, (angle_t)(frame * 500));
    mat4_translate(&trn, v3(FX_FRAC(-11,10), 0, FX_FRAC(-6,10)));
    mat4_mul(&model, &trn, &rot);
    mat4_mul(&mvp, &vp, &model);
#ifdef DUMP_MAT
    MASKED(1) {
        putc_('M');
        for (int c2 = 0; c2 < 4; c2++) { putc_(' '); hex_((unsigned)mvp.m[0][c2]); }
        putc_(' '); putc_('|');
        for (int c2 = 0; c2 < 4; c2++) { putc_(' '); hex_((unsigned)model.m[0][c2]); }
        putc_('\n');
    }
#endif
    draw_mesh(&cube, &mvp, col_a);
#ifdef TRACE_ZSUM
    say("zsumA ", raster_zsum());
#endif

    mat4_rot_x(&rot, (angle_t)(frame * 700));
    mat4_translate(&trn, v3(FX_FRAC(4,10), 0, FX_FRAC(4,10)));
    mat4_mul(&model, &trn, &rot);
    mat4_mul(&mvp, &vp, &model);
    draw_mesh(&cube, &mvp, col_b);
#ifdef TRACE_ZSUM
    say("zsumB ", raster_zsum());
#endif
}
