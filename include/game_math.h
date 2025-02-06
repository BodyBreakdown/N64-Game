#ifndef GAME_MATH_H
#define GAME_MATH_H
#include <stdint.h>
#include <math.h>

#define i8 int8_t
#define u8 uint8_t
#define i16 int16_t
#define u16 uint16_t
#define i32 int32_t
#define u32 uint32_t
#define i64 int64_t
#define u64 uint64_t

typedef struct
{
    float x, y;
} Vec2;

static inline i8 i8_sign(i8 x)
{
    return (x >> 7) | (!!x);
}

static inline i8 i8_bit_clamp(i8 x, i8 min, i8 max)
{
    i8 belowMin = (x - min) >> 7;
    i8 aboveMax = (max - x) >> 7;
    return (aboveMax & max) | (~aboveMax & ((belowMin & min) | (~belowMin & x)));
}

static inline Vec2 vec2_sqr(Vec2 vec)
{
    return (Vec2){vec.x * vec.x, vec.y * vec.y};
}

static inline Vec2 vec2_multiply(Vec2 vec1, Vec2 vec2)
{
    return (Vec2) {vec1.x * vec2.x, vec1.y * vec2.y};
}

static inline Vec2 vec2_normalize(Vec2 vec)
{
    float length = sqrtf(vec.x * vec.x + vec.y * vec.y);
    if(length > 0)
    {
        float invLen = 1 /length;
        vec.y *= invLen;
        vec.x *= invLen;
    }
    return vec;
}

#endif