#ifndef RENDER_HELPER_H
#define RENDER_HELPER_H

#include <display.h>
#include <game_math.h>
#include <libdragon.h>
#include <t3d/t3d.h>

static inline void fog_enable(color_t fogColor, float start, float end)
{
    //rdpq_mode_blender(RDPQ_BLENDER((IN_RGB, SHADE_ALPHA, FOG_RGB, INV_MUX_ALPHA)));
    rdpq_mode_fog(RDPQ_BLENDER((IN_RGB, SHADE_ALPHA, FOG_RGB, INV_MUX_ALPHA)));
    //RDPQ_FOG_STANDARD
    rdpq_set_fog_color(fogColor);
    t3d_fog_set_enabled(true);
    t3d_fog_set_range(start, end);
}

#endif // RENDER_HELPER_H
