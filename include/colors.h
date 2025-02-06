#ifndef COLORS_H
#define COLORS_H

#define WHITE   0xFFFFFFFF
#define BLACK   0x00000000
#define RED     0xFF0000FF
#define GREEN   0x00FF00FF
#define BLUE    0x0000FFFF

/*if(!bgBlock)
{
    rspq_block_begin();

    rdpq_set_mode_copy(false);
    rdpq_sprite_blit(bgSprite, 0, 0, &(rdpq_blitparms_t)
    {
        .scale_x = 0.9f,
        .scale_y = 0.9f,
    });

    rdpq_set_mode_standard();
    rdpq_mode_filter(FILTER_POINT);
    rdpq_mode_alphacompare(1);
    rdpq_mode_antialias(false);
    rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);

    bgBlock = rspq_block_end();
}
rspq_block_run(bgBlock);*/
#endif