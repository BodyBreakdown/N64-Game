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



i8 i8_sign(i8 x);
i8 i8_bit_clamp(i8 x, i8 min, i8 max);

Vec2 vec2_sqr(Vec2 v);
Vec2 vec2_multiply(Vec2 v1, Vec2 v2);
Vec2 vec2_normalize(Vec2 v);

#endif