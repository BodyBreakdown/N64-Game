#include "game_math.h"

float vec2_angle(Vec2 v1, Vec2 v2)
{
    return fm_atan2f(v2.y - v1.y, v2.x - v1.x);    
}



i8 i8_sign(i8 x)
{
    return (x >> 7) | (!!x);
}

i8 i8_bit_clamp(i8 x, i8 min, i8 max)
{
    i8 belowMin = (x - min) >> 7;
    i8 aboveMax = (max - x) >> 7;
    return (aboveMax & max) | (~aboveMax & ((belowMin & min) | (~belowMin & x)));
}

Vec2 vec2_sqr(Vec2 v)
{
    return (Vec2){{v.x * v.x, v.y * v.y}};
}

Vec2 vec2_multiply(Vec2 v1, Vec2 v2)
{
    return (Vec2){{v1.x * v2.x, v1.y * v2.y}};
}

Vec2 vec2_normalize(Vec2 v)
{
    float length = sqrtf(v.x * v.x + v.y * v.y);
    if (length > 0)
    {
        float invLen = 1 / length;
        v.y *= invLen;
        v.x *= invLen;
    }
    return v;
}
