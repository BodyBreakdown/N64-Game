#include "game_object.h"

GameObject* game_object_create(u32 id, T3DModel *model, u8 displayType)
{
    GameObject *obj = malloc_uncached(sizeof(GameObject));

    obj->id = id;
    obj->isDirty = true;
    obj->position = Vec3Zero;
    obj->rotation = Vec3Zero;
    obj->scale = (T3DVec3){{0.1f, 0.1f, 0.1f}};
    obj->model = model;
    obj->matrix = malloc_uncached(sizeof(T3DMat4FP));

    switch (displayType)
    {
        default:
            rspq_block_begin();
            t3d_model_draw(model);
            obj->displayCommand = rspq_block_end();
            break;
        case DisplaySky:
            rspq_block_begin();
            rdpq_mode_zbuf(false, false);
            t3d_model_draw(model);
            rdpq_mode_zbuf(true, true);
            obj->displayCommand = rspq_block_end();
            break;
    }
    t3d_mat4fp_identity(obj->matrix);
    return obj;
}
void game_object_update(GameObject *obj)
{
    t3d_mat4fp_from_srt_euler(obj->matrix, obj->scale.v, obj->rotation.v, obj->position.v);
    obj->isDirty = false;
}

void game_object_draw(GameObject *obj)
{
    t3d_matrix_set(obj->matrix, true);
    rspq_block_run(obj->displayCommand);   
}

void game_object_delete(GameObject *obj)
{
    free_uncached(obj->matrix);
    free_uncached(obj);

}