#include <stdio.h>
#include <stdint.h>
#include <libdragon.h>
#include "object3d.h"
#include "game_math.h"
#include "game_time.h"
#include "colors.h"
#include "microuiN64.h"

static joypad_inputs_t inputs;
static Vec2 inputAxes = {0};

static bool cube_visible = true;
static int capture_cube = 1;
static mu_Rect cube_win_rect = (mu_Rect){114, 110, 80, 80};
static int capture_screen = 1;
static int capture_count = 1;
static float clear_color[3] = {0.05f, 0.05f, 0.05f};
static float hue = 0.42f;
static float box_rot = 0.0f;

void DrawDebug()
{
    mu64_set_mouse_speed(0.000004f * deltaTime);
    if(mu_begin_window_ex(&mu_ctx, "Test Window", mu_rect(12, 20, 90, 140), MU_OPT_NOCLOSE))
    {
        mu_layout_row(&mu_ctx, 1, (int[]){-1}, 0);
        mu_label(&mu_ctx, "Background");

        if (mu_button(&mu_ctx, "Remove Screen"))
        {
            if (capture_count > 0)
                --capture_count;
        }
        if (mu_button(&mu_ctx, "Add Screen"))
        {
            ++capture_count;
        }

        if (mu_header_ex(&mu_ctx, "Time", MU_OPT_EXPANDED))
        {
            float fps = display_get_fps();

            char fps_buffer[16] = {0};

            mu_label(&mu_ctx, fps_buffer);

            mu_label(&mu_ctx, fps_buffer);
        }
        mu_end_window(&mu_ctx);

    }
}

int main(void)
{
    asset_init_compression(2);
    //static const resolution_t resolution = {.width = 400L, .height = 300L, .interlaced = (interlace_mode_t)0U};
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS);

    dfs_init(DFS_DEFAULT_LOCATION);
    rdpq_init();
    joypad_init();
    timer_init();
    
    t3d_init((T3DInitParams){});
    T3DViewport viewport = t3d_viewport_create();

    T3DModel* model = t3d_model_load("rom:/rat.t3dm");
    T3DMat4 modelMat;
    t3d_mat4_identity(&modelMat);
    T3DMat4FP* modelMatFP = malloc_uncached(sizeof(T3DMat4FP));
    
    T3DModel* sky = t3d_model_load("rom:/sky.t3dm");
    T3DMat4 skyMat;
    t3d_mat4_identity(&skyMat);
    T3DMat4FP* skyMatFP = malloc_uncached(sizeof(T3DMat4FP));
    
    T3DVec3 camPos = {{0, 10, 40}};
    T3DVec3 camTarget = {{0, 10, 0}};
    t3d_viewport_set_projection(&viewport, T3D_DEG_TO_RAD(70), 2, 100);

    
    u8 colorAmb[4] = {40, 50, 100, 255};
    u8 colorSun[4] = {250, 250, 230, 255};
    T3DVec3 lightDirVec = {{-1, 1, 1}};
    t3d_vec3_norm(&lightDirVec);

    rspq_block_t* dplDraw = NULL;

    const rdpq_font_t* font = rdpq_font_load("rom:/Readable9x4.font64");
    rdpq_text_register_font(1, font);

    mu64_init((joypad_port_t)0, 1);

    init_timers(TICK_30_PER_SECOND);
    float rotAngle = 0;

    while(1) 
    {
        update_timers();
        joypad_poll();
        mu64_start_frame();
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
            if (inputs.analog_l > 0)
            {
                camPos.y -= deltaTime * 10;
            }
            if (inputs.analog_r > 0)
            {
                camPos.y += deltaTime * 10;
            }

            float sin;
            float cos;
            fm_sincosf(rotAngle, &sin, &cos);
            T3DVec3 forward = {{sin, 0, cos}};
            T3DVec3 right = {{-cos, 0, sin}};

            camPos.x += ((right.x * inputAxes.x) + (forward.x * inputAxes.y)) * deltaTime * 10;
            camPos.z += ((right.z * inputAxes.x) + (forward.z * inputAxes.y)) * deltaTime * 10;
            
            camTarget.x = forward.x + camPos.x;
            camTarget.y = camPos.y;
            camTarget.z = forward.z + camPos.z;
        }     

        t3d_viewport_look_at(&viewport, &camPos, &camTarget, &(T3DVec3){{0,1,0}});

        t3d_mat4_from_srt_euler(
            &skyMat,
            (float[3]){1, 1, 1},
            (float[3]){0, 0, 0},
            (float[3]){camPos.x, camPos.y, camPos.z});

        t3d_mat4_from_srt_euler(
            &modelMat,
            (float[3]){0.1f, 0.1f, 0.1f},
            (float[3]){0, 0, 0},
            (float[3]){0, 0, 0});

        t3d_mat4_to_fixed(modelMatFP, &modelMat);
        t3d_mat4_to_fixed(skyMatFP, &skyMat);

        mu64_end_frame();
        
        
        surface_t *display = 0;
        display = display_get();
        rdpq_attach(display, display_get_zbuf());
        t3d_frame_start();
        t3d_viewport_attach(&viewport);
        t3d_screen_clear_color(RGBA32(40, 60, 70, 255));
        t3d_screen_clear_depth();
        t3d_light_set_ambient(colorAmb);
        t3d_light_set_directional(0, colorSun, &lightDirVec);
        t3d_light_set_count(1);

        if(!dplDraw)
        {
            rspq_block_begin();
            
            rdpq_mode_zbuf(false, false);
            t3d_matrix_push(skyMatFP);
            t3d_model_draw(sky);
            t3d_matrix_pop(1);
            rdpq_mode_zbuf(true, true);
            
            t3d_matrix_push(modelMatFP);
            t3d_model_draw(model);
            t3d_matrix_pop(1);
            
            dplDraw = rspq_block_end();
        }
        rspq_block_run(dplDraw);


        mu64_draw();
        rdpq_detach_show();

    }
    t3d_destroy();
    return 0;
}
