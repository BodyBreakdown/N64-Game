#include "game_math.h"

float wrap_angle(float angle)
{
    float a = fm_fmodf(angle + FM_PI, FM_PI * 2);
    if (a < 0) a += FM_PI * 2;
    return a - FM_PI;
}
