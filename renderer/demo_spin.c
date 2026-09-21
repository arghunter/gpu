#include "gpu.h"
#include "camera.h"
#include "mesh.h"
#include "geom.h"
#include "raster.h"

/* Spinning lit icosahedron.
 *
 * The camera ORBITS at a fixed radius rather than dollying in. That keeps
 * every vertex well clear of the near plane, which matters: near-plane
 * clipping produces slivers that still trip a register-allocation hazard in
 * the masked rasteriser inner loop. Orbiting is also what you actually want
 * to look at, so the constraint costs nothing here.
 *
 * Lighting is flat per triangle -- one normalise and one dot per face, none
 * per pixel. That is the difference between coloured polygons and something
 * that reads as a solid object, for essentially no cost. */

#define PHI  FX_FRAC(1618034, 1000000)
#define ONE  FX_ONE
#define ORBIT_R 5

#define V(x,y,z) { { (x), (y), (z) }, { 0,0,0 }, 0, 0 }
static const vertex_t ico_v[12] = {
    V(-ONE,  PHI,    0), V( ONE,  PHI,    0), V(-ONE, -PHI,    0), V( ONE, -PHI,    0),
    V(   0, -ONE,  PHI), V(   0,  ONE,  PHI), V(   0, -ONE, -PHI), V(   0,  ONE, -PHI),
    V( PHI,    0, -ONE), V( PHI,    0,  ONE), V(-PHI,    0, -ONE), V(-PHI,    0,  ONE),
};
/* Wound counter-clockwise seen from outside. geom_to_screen flips Y, so a
 * front face ends up with negative screen area -- which is what raster_tri
 * culls on. */
static const unsigned short ico_i[60] = {
     0,11, 5,  0, 5, 1,  0, 1, 7,  0, 7,10,  0,10,11,
     1, 5, 9,  5,11, 4, 11,10, 2, 10, 7, 6,  7, 1, 8,
     3, 9, 4,  3, 4, 2,  3, 2, 6,  3, 6, 8,  3, 8, 9,
     4, 9, 5,  2, 4,11,  6, 2,10,  8, 6, 7,  9, 8, 1,
};
static const mesh_t ico = { ico_v, ico_i, 12, 20 };

/* Face colours cycle so adjacent faces stay distinguishable even where the
 * lighting is similar. */
static const unsigned int face_col[20] = {
    0xE05050,0xE08040,0xE0C040,0xA0D040,0x50C060,0x40C0A0,0x40A0E0,0x5060E0,
    0x8050E0,0xC050C0,0xE05080,0xD07060,0xC0A050,0x90C050,0x50B080,0x50A0C0,
    0x7080D0,0xA070C0,0xC060A0,0xD06070,
};

static unsigned int shade(unsigned int c, fx k) {
    unsigned int r = (c >> 16) & 0xFF, g = (c >> 8) & 0xFF, b = c & 0xFF;
    r = (unsigned int)(((long long)r * k) >> FX_SHIFT);
    g = (unsigned int)(((long long)g * k) >> FX_SHIFT);
    b = (unsigned int)(((long long)b * k) >> FX_SHIFT);
    return (r << 16) | (g << 8) | b;
}

unsigned int g_clear_us, g_tri_us;

void render_frame(int frame) {
    unsigned int ta = TIMER_US;
    raster_clear(0x101820);
    g_clear_us = TIMER_US - ta;

    /* Orbit. angle_t wraps on its own, so the frame counter can run forever. */
    angle_t a = (angle_t)(frame * 300);
    camera_t cam;
    cam_init(&cam, SCREEN_W, SCREEN_H);
    cam.pos = v3(fx_mul(FX(ORBIT_R), fx_sin(a)),
                 FX(2),
                 fx_mul(FX(ORBIT_R), fx_cos(a)));
    cam_look_at(&cam, v3(0, 0, 0));

    mat4 vp, model, rx, mvp;
    cam_viewproj(&cam, &vp);
    mat4_rot_x(&rx, (angle_t)(frame * 170));
    mat4_rot_y(&model, (angle_t)(frame * 90));
    mat4_mul(&model, &model, &rx);
    mat4_mul(&mvp, &vp, &model);

    vec3 light = v3_normalize(v3(FX_FRAC(4,10), FX_FRAC(8,10), FX_FRAC(5,10)));

    for (int t = 0; t < ico.ntris; t++) {
        const vertex_t* v0 = &ico.verts[ico.idx[t*3+0]];
        const vertex_t* v1 = &ico.verts[ico.idx[t*3+1]];
        const vertex_t* v2 = &ico.verts[ico.idx[t*3+2]];

        /* Object-space face normal, rotated into world space. model is a pure
         * rotation, so mul_dir is the correct transform for a normal. */
        vec3 n = v3_normalize(v3_cross(v3_sub(v1->pos, v0->pos),
                                       v3_sub(v2->pos, v0->pos)));
        n = mat4_mul_dir(&model, n);
        /* Ambient + diffuse rather than a bare clamp: a pure Lambert term
         * leaves back faces almost black and the object reads as a
         * silhouette instead of a solid. */
        fx d = v3_dot(n, light);
        if (d < 0) d = 0;
        d = FX_FRAC(35,100) + fx_mul(FX_FRAC(65,100), d);
        unsigned int col = shade(face_col[t], d);

        vec4 cl[3];
        cl[0] = mat4_mul_point(&mvp, v0->pos);
        cl[1] = mat4_mul_point(&mvp, v1->pos);
        cl[2] = mat4_mul_point(&mvp, v2->pos);

        vec4 poly[6];
        int ntri = geom_clip_near(cl, poly);
        for (int i = 0; i < ntri; i++) {
            svert_t sv[3];
            int ok = 1;
            for (int k = 0; k < 3; k++)
                ok &= geom_to_screen(poly[i*3+k], col, &sv[k]);
            if (ok) raster_tri(&sv[0], &sv[1], &sv[2]);
        }
    }
    g_tri_us = TIMER_US - ta - g_clear_us;
}
