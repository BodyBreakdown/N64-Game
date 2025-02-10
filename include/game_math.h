#ifndef GAME_MATH_H
#define GAME_MATH_H

#include <fmath.h>
#include <stdint.h>

#define i8 int8_t
#define u8 uint8_t
#define i16 int16_t
#define u16 uint16_t
#define i32 int32_t
#define u32 uint32_t
#define i64 int64_t
#define u64 uint64_t

#define Vec2Zero    (Vec2){{0, 0}}
#define Vec2One    (Vec2){{1, 1}}
#define Vec2UnitX   (Vec2){{1, 0}}
#define Vec2UnitY   (Vec2){{0, 1}}

#define Vec3Zero    (T3DVec3){{0, 0, 0}}
#define Vec3One     (T3DVec3){{1, 1, 1}}
#define Vec3UnitX   (T3DVec3){{1, 0, 0}}
#define Vec3UnitY   (T3DVec3){{0, 1, 0}}
#define Vec3UnitZ   (T3DVec3){{0, 0, 1}}

typedef union
{
    struct
    {
        float x, y;
    };  
    float v[2];
} Vec2;

inline i8 i8_sign(i8 x)
{
    return (x >> 7) | (!!x);
}
i8 i8_bit_clamp(i8 x, i8 min, i8 max);

inline float vec2_angle(Vec2 v1, Vec2 v2)
{
    return fm_atan2f(v2.y - v1.y, v2.x - v1.x);
}

inline Vec2 vec2_sqr(Vec2 v)
{
    return (Vec2){{v.x * v.x, v.y * v.y}};
}

inline Vec2 vec2_multiply(Vec2 v1, Vec2 v2)
{
    return (Vec2){{v1.x * v2.x, v1.y * v2.y}};
}

inline Vec2 vec2_normalize(Vec2 v)
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

#endif