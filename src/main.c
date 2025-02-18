#include <stdio.h>
#include "scenes.h"
#include "colors.h"


GameState gameState = 0;

int main(void)
{
    asset_init_compression(2);
    //static const resolution_t resolution = {.width = 400L, .height = 300L, .interlaced = (interlace_mode_t)0U};
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
    debug_init_isviewer();
    debug_init_usblog();
    dfs_init(DFS_DEFAULT_LOCATION);
    rdpq_init();
    input_init();

    timer_init();
    rdpq_text_register_font(FONT_BUILTIN_DEBUG_MONO, rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_MONO));

    
    t3d_init((T3DInitParams){});
    T3DViewport viewport = t3d_viewport_create();


    mainCam = camera_create(&viewport, 70, 15, 200);

    
    u8 colorAmb[4] = { 80, 40, 70, 255 };
    u8 colorSun[4] = {252, 250, 240, 255};
    T3DVec3 lightDirVec = {{-1, 1, 1}};
    t3d_vec3_norm(&lightDirVec);
    const rdpq_font_t* font = rdpq_font_load("rom:/Readable9x4.font64");
    rdpq_text_register_font(2, font);
    init_timers(TICK_30_PER_SECOND);

    gameState = LOGOS;
    rspq_syncpoint_t syncPoint = 0;
    
    LogosStart();

    while(1) 
    {
        
        update_timers();
        input_update(input);
        
        switch(gameState)
        {
            case LOGOS: 
                LogosUpdate(); 
                break; 

            // case TITLE: TitleUpdate(); break;
            // case OPTIONS: OptionsUpdate(); break;
            case GAMEPLAY:
                GameUpdate();
                break;
        }
        //mainCam.position.y += deltaTime;

        camera_update(&mainCam);
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
            case GAMEPLAY: 
                GameDraw(); 
                break;
        }
        //syncPoint = rspq_syncpoint_new();
        

        rdpq_detach_show();
    }

    t3d_destroy();
    return 0;
}
