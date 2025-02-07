
#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "game_math.h"
#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include <t3d/t3dmath.h>

typedef struct 
{
    u32 id;
    rspq_block_t* displayCommand;
    T3DMat4FP* matrix;
    float position[3];
    float rotation[3];
    float scale[3];
} Object3D;

Object3D model_create(u32 id, rspq_block_t* displayCommand);
void model_delete(Object3D* model);

#endif