#include "object3d.h"

Object3D object3d_create(u32 id, rspq_block_t *displayCommand)
{
    Object3D obj = (Object3D)
    {
        .id = id,
        .position = Vec3Zero,
        .rotation = Vec3Zero,
        .scale = Vec3One,
        .displayCommand = displayCommand,
        .matrix = malloc_uncached(sizeof(T3DMat4FP))
    };

    t3d_mat4fp_identity(obj.matrix);
    return obj;
}
void object3d_delete(Object3D *obj)
{
    free_uncached(obj->matrix);
}