#include "camera.h"

#define FOV_MIN ANG_FROM_DEG(5)
#define FOV_MAX ANG_FROM_DEG(170)

void cam_init(camera_t* c, int vp_w, int vp_h) {
    c->pos   = v3(0, 0, 0);
    c->yaw   = 0;
    c->pitch = 0;
    c->roll  = 0;
    c->fov   = ANG_FROM_DEG(60);
    /* znear deliberately not tiny: depth precision in Q16.16 degrades with
     * the near/far ratio, and 1/znear is what drives the projection. */
    c->znear = FX(1);
    c->zfar  = FX(1000);
    c->vp_w  = vp_w;
    c->vp_h  = vp_h;
}

void cam_world(const camera_t* c, mat4* out) {
    mat4 ry, rx, rz, t;
    mat4_rot_y(&ry, c->yaw);
    mat4_rot_x(&rx, c->pitch);
    mat4_rot_z(&rz, c->roll);
    mat4_mul(&ry, &ry, &rx);
    mat4_mul(&ry, &ry, &rz);
    mat4_translate(&t, c->pos);
    mat4_mul(out, &t, &ry);
}

void cam_view(const camera_t* c, mat4* out) {
    mat4 w;
    cam_world(c, &w);
    mat4_rigid_inverse(out, &w);
}

void cam_basis(const camera_t* c, vec3* right, vec3* up, vec3* fwd) {
    mat4 w;
    cam_world(c, &w);
    if (right) *right = v3(w.m[0][0], w.m[1][0], w.m[2][0]);
    if (up)    *up    = v3(w.m[0][1], w.m[1][1], w.m[2][1]);
    if (fwd)   *fwd   = v3(-w.m[0][2], -w.m[1][2], -w.m[2][2]);
}

void cam_proj(const camera_t* c, mat4* out) {
    angle_t fov = c->fov;
    if (fov < FOV_MIN) fov = FOV_MIN;
    if (fov > FOV_MAX) fov = FOV_MAX;

    angle_t h = (angle_t)(fov / 2);
    fx f = fx_div(fx_cos(h), fx_sin(h));         /* cot(fov/2) */
    fx aspect = FX_FRAC(c->vp_w, c->vp_h);

    fx zn = c->znear, zf = c->zfar, dz = zn - zf;

    for (int r = 0; r < 4; r++) for (int cc = 0; cc < 4; cc++) out->m[r][cc] = 0;
    out->m[0][0] = fx_div(f, aspect);
    out->m[1][1] = f;
    out->m[2][2] = fx_div(zf + zn, dz);
    out->m[2][3] = fx_div(fx_mul(FX(2), fx_mul(zf, zn)), dz);
    out->m[3][2] = -FX_ONE;
    out->m[3][3] = 0;
}

void cam_viewproj(const camera_t* c, mat4* out) {
    mat4 v, p;
    cam_view(c, &v);
    cam_proj(c, &p);
    mat4_mul(out, &p, &v);
}

void cam_look_at(camera_t* c, vec3 target) {
    vec3 d = v3_sub(target, c->pos);
    if (d.x == 0 && d.y == 0 && d.z == 0) return;
    /* Forward is the negated Z column of Ry(yaw)*Rx(pitch):
     *   fwd = (-sin(yaw)cos(pitch), sin(pitch), -cos(yaw)cos(pitch))
     * so tan(yaw) = (-d.x)/(-d.z). Both signs matter -- dropping them
     * mirrors the yaw about the Z axis. */
    c->yaw = fx_atan2(-d.x, -d.z);
    vec3 flat = v3(d.x, 0, d.z);
    c->pitch = fx_atan2(d.y, v3_length(flat));
}

void cam_move_local(camera_t* c, vec3 d) {
    vec3 right, up, fwd;
    cam_basis(c, &right, &up, &fwd);
    c->pos = v3_add(c->pos, v3_scale(right, d.x));
    c->pos = v3_add(c->pos, v3_scale(up,    d.y));
    c->pos = v3_add(c->pos, v3_scale(fwd,   d.z));
}
