#ifndef CAMERA_H
#define CAMERA_H

#include "vec.h"

/* Camera pose and lenses.
 *
 * Right-handed world space, OpenGL convention: +X right, +Y up, and the
 * camera looks down -Z when all angles are zero.
 *
 *   yaw   rotates about +Y; increasing turns left (CCW seen from above)
 *   pitch rotates about +X; positive looks up
 *   roll  rotates about the view axis
 *
 * Angles are binary (65536 per turn) so they wrap for free and never need
 * clamping to a range. Every field is plain data -- set them directly, or
 * use the helpers. */

typedef struct {
    vec3    pos;
    angle_t yaw, pitch, roll;
    angle_t fov;                /* full vertical field of view */
    fx      znear, zfar;
    int     vp_w, vp_h;         /* viewport in pixels, for aspect */
} camera_t;

void cam_init(camera_t* c, int vp_w, int vp_h);

/* Orthonormal camera axes in world space. fwd is the direction the camera
 * looks, i.e. the -Z column, so it can be used directly for movement. */
void cam_basis(const camera_t* c, vec3* right, vec3* up, vec3* fwd);

/* Camera-to-world (the pose) and its inverse (the view matrix). */
void cam_world(const camera_t* c, mat4* out);
void cam_view(const camera_t* c, mat4* out);

/* Perspective projection. fov is clamped away from the degenerate ends
 * because cot(fov/2) goes to infinity at 0 and to zero at a half turn. */
void cam_proj(const camera_t* c, mat4* out);
void cam_viewproj(const camera_t* c, mat4* out);

/* Point the camera at a world position by solving for yaw and pitch. Leaves
 * roll alone. A target coincident with the eye is ignored. */
void cam_look_at(camera_t* c, vec3 target);

/* Translate along the camera's own axes: d.x right, d.y up, d.z forward. */
void cam_move_local(camera_t* c, vec3 d);

#endif /* CAMERA_H */
