#ifndef GEOM_H
#define GEOM_H

#include "vec.h"

/* Screen coordinates are Q28.4: 1/16 of a pixel.
 *
 * This is NOT Q16.16. Screen values reach 320*16 = 5120 and the rasteriser's
 * cross products multiply coordinate differences together, which would blow
 * past Q16.16's 32767 ceiling immediately. Keeping the two formats distinct,
 * and saying so at every boundary, is the whole defence against the class of
 * overflow that broke the previous renderer. */
#define SUBPIX      4
#define SUBPIX_ONE  (1 << SUBPIX)

/* Reciprocal depth in Q2.30. invw lies in (0, 1/znear], and Q16.16 would
 * give it only ~10 bits of range at the far plane -- two surfaces one unit
 * apart at z=500 differ by 4e-6, which rounds to nothing in Q16.16 but is
 * 4295 counts here. Larger and it overflows; smaller and distant geometry
 * z-fights. */
typedef int zfx;
#define Z_SHIFT 30
#define Z_ONE   ((zfx)(1 << Z_SHIFT))

/* A vertex after projection, ready for the rasteriser. */
typedef struct {
    int          x, y;      /* Q28.4 screen */
    zfx          invw;      /* Q2.30 */
    unsigned int col;
} svert_t;

/* Triangles are rejected outright if any vertex lands beyond this many
 * pixels from the viewport. Inside the band the rasteriser's edge values are
 * provably under 1.4e9 and fit int32; outside, they would wrap silently.
 * Near-plane clipping removes the common cause of far-flung vertices, so in
 * practice this only fires on geometry that is mostly off screen. */
#define GUARD_PX    1024
#define GUARD_SUB   (GUARD_PX * SUBPIX_ONE)

/* Clip a triangle against the near plane in homogeneous space, before the
 * perspective divide. Writes up to 2 triangles (6 vec4) and returns the
 * triangle count: 0 when fully behind, 1 when one or three vertices survive,
 * 2 when two do. */
int geom_clip_near(const vec4 in[3], vec4 out[6]);

/* Perspective divide and viewport transform. Returns 0 if the vertex is
 * outside the guard band or has a non-positive w. */
int geom_to_screen(vec4 clip, unsigned int col, svert_t* out);

#endif /* GEOM_H */
