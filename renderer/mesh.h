#ifndef MESH_H
#define MESH_H

#include "vec.h"

/* Normals and texture coordinates are carried from M1 even though nothing
 * reads them yet, so adding lighting (M4) and textures (M5) does not change
 * the vertex format or invalidate any mesh data. */
typedef struct {
    vec3 pos;
    vec3 nrm;
    fx   u, v;
} vertex_t;

typedef struct {
    const vertex_t*       verts;
    const unsigned short* idx;      /* 3 per triangle */
    int                   nverts;
    int                   ntris;
} mesh_t;

#endif /* MESH_H */
