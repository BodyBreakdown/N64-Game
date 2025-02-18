#ifndef COLLISION_H
#define COLLISION_H

#include <t3d/t3d.h>

typedef struct
{
    uint32_t indices[4];
} Tri;

typedef struct
{
    uint32_t vtxCount;
    T3DVec3* vtx;
    uint32_t nrmCount;
    T3DVec3* nrms;
    uint32_t triCount;
    Tri* tris;
} MeshData;

#endif // COLLISION_H