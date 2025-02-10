#include "scenes.h"

static GameObject* logo;

void LogosStart(void)
{
    logo = game_object_create(0, t3d_model_load("rom:/chest.t3dm"), 0);

}

void LogosUpdate(void)
{
    float angle = fm_fmodf(accumulator, 6.28319);
    float scale = ((fm_sinf(angle)/FM_PI)+1)/2;
    for (int i = 0; i < 3; i++)
    {
        logo->scale.v[i] = 0.1f * fm_lerp(0.5f, 2, scale);
    }
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