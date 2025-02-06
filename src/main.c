#include <stdio.h>
#include <stdint.h>
#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/t3dmodel.h>
#include "game_math.h"
#include "game_time.h"
#include "colors.h"


static joypad_inputs_t inputs;
static Vec2 inputAxes = {0};

#define AxisRange 100;

int main(void)
{
    asset_init_compression(2);
    display_init(RESOLUTION_512x480, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS_DEDITHER);

    dfs_init(DFS_DEFAULT_LOCATION);
    rdpq_init();
    joypad_init();
    timer_init();
    
    t3d_init((T3DInitParams){});
    T3DViewport viewport = t3d_viewport_create();
    
    T3DMat4 modelMat;
    t3d_mat4_identity(&modelMat);
    T3DMat4FP* modelMatFP = malloc_uncached(sizeof(T3DMat4FP));
    
    T3DVec3 camPos = {{0, 10, 40}};
    T3DVec3 camTarget = {{0, 10, 0}};
    t3d_viewport_set_projection(&viewport, T3D_DEG_TO_RAD(70), 2, 100);

    u8 colorAmb[4] = {40, 50, 100, 255};
    u8 colorSun[4] = {250, 250, 230, 255};
    T3DVec3 lightDirVec = {{-1, 1, 1}};
    t3d_vec3_norm(&lightDirVec);

    T3DModel* model = t3d_model_load("rom:/rat.t3dm");

    float rotAngle = 0;

    rspq_block_t* dplDraw = NULL;

    rdpq_font_t *nuFont = rdpq_font_load("rom:/Noita.font64");
    rdpq_font_style(nuFont, 0, &(rdpq_fontstyle_t){.color = RGBA32(255, 255, 255, 255)});
    rdpq_text_register_font(1, nuFont);
    const char* txt = "Hello.\nThis is my own custom font being drawn on a Nintendo 64. \n:]";
    int txtLength = strlen(txt);

    init_timers(TICK_30_PER_SECOND);

    while(1) 
    {
        update_timers();
        joypad_poll();

        if(joypad_is_connected((joypad_port_t)0))
        {
            inputs = joypad_get_inputs((joypad_port_t)0);
            inputAxes.x = abs(inputs.stick_x) > 5 ? i8_bit_clamp(inputs.stick_x, -75, 75) : 0;
            inputAxes.y = abs(inputs.stick_y) > 5 ? i8_bit_clamp(inputs.stick_y, -75, 75) : 0;

            inputAxes = vec2_normalize(inputAxes);
            
            if (inputs.cstick_x != 0)
            {
                rotAngle -= deltaTime * i8_sign(inputs.cstick_x);
            }

            float sin = sinf(rotAngle);
            float cos = cosf(rotAngle);

            T3DVec3 forward = {{sin, 0, cos}};
            T3DVec3 right = {{-cos, 0, sin}};

            camPos.x += ((right.x * inputAxes.x) + (forward.x * inputAxes.y)) * deltaTime * 10;
            camPos.z += ((right.z * inputAxes.x) + (forward.z * inputAxes.y)) * deltaTime * 10;
            
            camTarget.x = forward.x + camPos.x;
            camTarget.z = forward.z + camPos.z;
        }
        

        t3d_viewport_look_at(&viewport, &camPos, &camTarget, &(T3DVec3){{0,1,0}});
        t3d_mat4_from_srt_euler(
            &modelMat,
            (float[3]){1, 1, 1},
            (float[3]){0, 0, 0},
            (float[3]){0, 0, 0}
        );
        t3d_mat4_to_fixed(modelMatFP, &modelMat);

        surface_t *display = 0;
        display = display_get();
        rdpq_attach(display, display_get_zbuf());

        t3d_frame_start();
        //rdpq_mode_zbuf(false, false);
        t3d_viewport_attach(&viewport);
        t3d_screen_clear_color(RGBA32(40,60,70,255));
        t3d_screen_clear_depth();
        t3d_light_set_ambient(colorAmb);
        t3d_light_set_directional(0, colorSun, &lightDirVec);
        t3d_light_set_count(1);

        if(!dplDraw)
        {
            rspq_block_begin();
            t3d_matrix_push(modelMatFP);
            t3d_model_draw(model);
            t3d_matrix_pop(1);
            dplDraw = rspq_block_end();
        }
        rspq_block_run(dplDraw);
        //rdpq_mode_zbuf(true, true);
        disable_interrupts();

        rdpq_paragraph_t *par = rdpq_paragraph_build(&(rdpq_textparms_t){
                                                         .align = ALIGN_CENTER,
                                                         .valign = VALIGN_CENTER,
                                                         .width = 500,
                                                         .height = 300,
                                                         .wrap = WRAP_WORD,
                                                     },
                                                     1, txt, &txtLength);

        rdpq_paragraph_render(par, 10, 10);
        rdpq_paragraph_free(par);
        enable_interrupts();

        rdpq_detach_show();

    }
    t3d_destroy();
    return 0;
}