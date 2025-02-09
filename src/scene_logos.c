#include "scenes.h"

static GameObject* logo;

void LogosStart(void)
{
    logo = game_object_create(0, t3d_model_load("rom:/n64.t3dm"), 0);
}

void LogosUpdate(void)
{   

    logo->rotation.y = fm_fmodf(logo->rotation.y + (deltaTime/4), 6.28319);
    t3d_mat4fp_from_srt_euler(logo->matrix, logo->scale.v, logo->rotation.v, logo->position.v);
}

void LogosDraw(void)
{

    t3d_matrix_push_pos(1);
    t3d_matrix_set(logo->matrix, true);
    rspq_block_run(logo->displayCommand);
    t3d_matrix_pop(1);


}