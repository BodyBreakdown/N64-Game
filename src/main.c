#include <stdio.h>
#include "scenes.h"
#include "colors.h"
#include "input.h"


joypad_inputs_t inputs = {0};
Vec2 inputAxes = {0};
GameState gameState = 0;

int main(void)
{
    asset_init_compression(2);
    //static const resolution_t resolution = {.width = 400L, .height = 300L, .interlaced = (interlace_mode_t)0U};
    display_init(RESOLUTION_640x480, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS);
    debug_init_isviewer();
    debug_init_usblog();
    dfs_init(DFS_DEFAULT_LOCATION);
    rdpq_init();
    joypad_init();
    timer_init();
    rdpq_text_register_font(FONT_BUILTIN_DEBUG_MONO, rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_MONO));
    t3d_debug_print_init();
    
    t3d_init((T3DInitParams){});
    T3DViewport viewport = t3d_viewport_create();

    Camera mainCam = camera_create(&viewport, 70, 2, 200);
    mainCam.position = (T3DVec3){{0, 5, 40}};

    
    u8 colorAmb[4] = {140, 140, 140, 255};
    u8 colorSun[4] = {250, 250, 250, 255};
    T3DVec3 lightDirVec = {{-1, 1, 1}};
    t3d_vec3_norm(&lightDirVec);


    const rdpq_font_t* font = rdpq_font_load("rom:/Readable9x4.font64");
    rdpq_text_register_font(2, font);
    
    init_timers(TICK_30_PER_SECOND);
    float rotAngle = 0;
    
    inputs = joypad_get_inputs((joypad_port_t)0);
    
    gameState = LOGOS;
    rspq_syncpoint_t syncPoint = 0;
    
    LogosStart();

    while(1) 
    {
        update_timers();
        joypad_poll();
        inputs = joypad_get_inputs((joypad_port_t)0);
        inputAxes.x = abs(inputs.stick_x) > 5 ? i8_bit_clamp(inputs.stick_x, -75, 75) : 0;
        inputAxes.y = abs(inputs.stick_y) > 5 ? i8_bit_clamp(inputs.stick_y, -75, 75) : 0;

        inputAxes = vec2_normalize(inputAxes);

        switch(gameState)
        {
            case LOGOS: LogosUpdate(); break;
            //case TITLE: TitleUpdate(); break;
            //case OPTIONS: OptionsUpdate(); break;
            //case GAMEPLAY: GameUpdate(); break;
        }
        mainCam.position.y += deltaTime;
        camera_update(&mainCam);

        lightDirVec.x += inputAxes.x * deltaTime * 3;
        lightDirVec.y += inputAxes.y * deltaTime * 3;
        t3d_vec3_norm(&lightDirVec);

        rdpq_attach(display_get(), display_get_zbuf());

        t3d_frame_start();
        t3d_viewport_attach(&viewport);
        t3d_screen_clear_color(RGBA32(12, 12, 12, 255));
        t3d_screen_clear_depth();
        t3d_light_set_ambient(colorAmb);
        t3d_light_set_directional(0, colorSun, &lightDirVec);
        t3d_light_set_count(1);

        switch (gameState)
        {
        case LOGOS:
            LogosDraw();
            break;
        //case TITLE: TitleDraw(); break;
        //case OPTIONS: OptionsDraw(); break;
        //case GAMEPLAY: GameDraw(); break;
        }
        syncPoint = rspq_syncpoint_new();
        t3d_debug_print_start();
        //t3d_debug_print(0, 0, TextFormat("%.2f, %.2f, %.2f", lightDirVec.x, lightDirVec.y, lightDirVec.z));
        rdpq_detach_show();
    }
    t3d_destroy();
    return 0;
}
