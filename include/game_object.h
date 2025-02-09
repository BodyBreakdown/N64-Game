
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "game_math.h"
#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include <t3d/t3dmath.h>

#define Display3D 0
#define DisplaySky 1

typedef struct 
{
    u32 id;
    bool isDirty;
    T3DModel* model;
    rspq_block_t* displayCommand;
    T3DVec3 position;
    T3DVec3 rotation;
    T3DVec3 scale;
    T3DMat4FP *matrix;
} GameObject;


GameObject* game_object_create(u32 id, T3DModel *model, u8 displayType);
void game_object_update(GameObject* obj);
void game_object_draw(GameObject* obj);
void game_object_delete(GameObject* obj);

#endif  