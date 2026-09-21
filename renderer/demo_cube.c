#include "gpu.h"
#include "camera.h"

/* M0: prove the transform chain end to end.
 *
 * Deliberately a scalar bounding-box rasteriser with integer screen
 * coordinates and no depth buffer -- lanes, subpixel precision and Z arrive
 * in M1/M2. A convex solid with backface culling renders correctly without a
 * depth buffer, which is why a cube is the right first subject: if the
 * matrices, winding or culling are wrong, it looks obviously wrong. */

static void put(int x, int y, unsigned int c) {
    if ((unsigned)x < SCREEN_W && (unsigned)y < SCREEN_H) FB[y * SCREEN_W + x] = c;
}

/* Returns 0 if the vertex is at or behind the eye plane, where the
 * perspective divide is meaningless. Proper near-plane clipping is M1. */
static int project(const mat4* mvp, vec3 p, int* sx, int* sy) {
    vec4 c = mat4_mul_point(mvp, p);
    if (c.w <= FX_ONE / 64) return 0;
    fx iw = fx_div(FX_ONE, c.w);
    fx nx = fx_mul(c.x, iw), ny = fx_mul(c.y, iw);
    *sx = fx_round_int(fx_mul(nx + FX_ONE, FX(SCREEN_W / 2)));
    *sy = fx_round_int(fx_mul(FX_ONE - ny, FX(SCREEN_H / 2)));
    return 1;
}

/* Integer edge functions. Screen coords reach 320 and the cross products
 * reach ~10^5, which overflows Q16.16 -- hence plain int here rather than fx.
 * This is the reason the real rasteriser will use Q28.4. */
static void fill_tri(int x0, int y0, int x1, int y1, int x2, int y2, unsigned int col) {
    /* Front faces have NEGATIVE screen area: they are wound CCW in world
     * space, and project() flips Y so that screen rows grow downward, which
     * reverses the sign. Culling on area <= 0 keeps the back faces and drops
     * the front ones -- the cube then renders inside out. */
    int area = (x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0);
    if (area >= 0) return;                       /* backface or degenerate */

    int minx = x0 < x1 ? (x0 < x2 ? x0 : x2) : (x1 < x2 ? x1 : x2);
    int maxx = x0 > x1 ? (x0 > x2 ? x0 : x2) : (x1 > x2 ? x1 : x2);
    int miny = y0 < y1 ? (y0 < y2 ? y0 : y2) : (y1 < y2 ? y1 : y2);
    int maxy = y0 > y1 ? (y0 > y2 ? y0 : y2) : (y1 > y2 ? y1 : y2);
    if (minx < 0) minx = 0;
    if (miny < 0) miny = 0;
    if (maxx > SCREEN_W - 1) maxx = SCREEN_W - 1;
    if (maxy > SCREEN_H - 1) maxy = SCREEN_H - 1;

    for (int y = miny; y <= maxy; y++)
        for (int x = minx; x <= maxx; x++) {
            int e0 = (x1 - x0) * (y - y0) - (y1 - y0) * (x - x0);
            int e1 = (x2 - x1) * (y - y1) - (y2 - y1) * (x - x1);
            int e2 = (x0 - x2) * (y - y2) - (y0 - y2) * (x - x2);
            if (e0 <= 0 && e1 <= 0 && e2 <= 0) put(x, y, col);
        }
}

static const signed char cube_v[8][3] = {
    {-1,-1,-1}, { 1,-1,-1}, { 1, 1,-1}, {-1, 1,-1},
    {-1,-1, 1}, { 1,-1, 1}, { 1, 1, 1}, {-1, 1, 1},
};
/* Counter-clockwise seen from outside, so the area sign culls back faces. */
static const unsigned char cube_i[12][3] = {
    {0,2,1},{0,3,2},  {4,5,6},{4,6,7},
    {0,1,5},{0,5,4},  {2,3,7},{2,7,6},
    {1,2,6},{1,6,5},  {0,4,7},{0,7,3},
};
static const unsigned int face_col[6] = {
    0xE04040, 0x40E040, 0x4040E0, 0xE0E040, 0xE040E0, 0x40E0E0,
};

void render_frame(int frame) {
    for (int i = 0; i < SCREEN_W * SCREEN_H; i++) FB[i] = 0x101018;

    camera_t cam;
    cam_init(&cam, SCREEN_W, SCREEN_H);
    cam.pos = v3(FX(0), FX(0), FX(5));
    cam_look_at(&cam, v3(0, 0, 0));

    mat4 model, ry, rx, vp, mvp;
    mat4_rot_y(&ry, (angle_t)(frame * 420));
    mat4_rot_x(&rx, (angle_t)(frame * 260));
    mat4_mul(&model, &ry, &rx);
    cam_viewproj(&cam, &vp);
    mat4_mul(&mvp, &vp, &model);

    int sx[8], sy[8], ok[8];
    for (int i = 0; i < 8; i++) {
        vec3 p = v3(FX(cube_v[i][0]), FX(cube_v[i][1]), FX(cube_v[i][2]));
        ok[i] = project(&mvp, p, &sx[i], &sy[i]);
    }
    for (int t = 0; t < 12; t++) {
        int a = cube_i[t][0], b = cube_i[t][1], c = cube_i[t][2];
        if (!ok[a] || !ok[b] || !ok[c]) continue;
        fill_tri(sx[a], sy[a], sx[b], sy[b], sx[c], sy[c], face_col[t / 2]);
    }
}
