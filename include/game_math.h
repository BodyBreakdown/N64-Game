#ifndef GAME_MATH_H
#define GAME_MATH_H

#include <fmath.h>
#include <stdint.h>
#include <t3d/t3d.h>

typedef int8_t s8;
typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef int32_t s32;
typedef uint32_t u32;
typedef int64_t s64;
typedef uint64_t u64;

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

inline static s8 s8_sign(s8 x)
{
    return (x >> 7) | (!!x);
}

inline static s16 s16_sign(s16 x)
{
    return (x >> 15) | (!!x);
}

inline static s32 s32_sign(s16 x)
{
    return (x >> 31) | (!!x);
}

inline static s64 s64_sign(s64 x)
{
    return (x >> 63) | (!!x);
}

#define sign(x) _Generic((x),   \
    s8: s8_sign,                \
    s16: s16_sign,              \
    s32: s32_sign,              \
    s64: s64_sign,              \
)(x)

inline s8 s8_clamp(s8 x, s8 min, s8 max)
{
    if (x >= max) return max;
    if (x <= min) return min;
    return x;
}

inline float vec2_angle(Vec2 v1, Vec2 v2)
{
    return fm_atan2f(v2.y - v1.y, v2.x - v1.x);
}

inline Vec2 vec2_sqr(Vec2 v)
{
    return (Vec2){{v.x * v.x, v.y * v.y}};
}

inline float vec2_sqr_mag(const Vec2* vec)
{
    return vec->v[0] * vec->v[0] + vec->v[1] * vec->v[1];
}

inline Vec2 vec2_multiply(Vec2 v1, Vec2 v2)
{
    return (Vec2){{v1.x * v2.x, v1.y * v2.y}};
}

inline void vec2_normalize(Vec2* v)
{
    float length = sqrtf(v->x * v->x + v->y * v->y);
    if (length < 0.0001f) length = 0.0001f;
    v->y /= length;
    v->x /= length;
}

float wrap_angle(float angle);



inline void vec3_right_from_matrix(T3DVec3* res, T3DMat4* mat)
{
    res->x = mat->m[0][0];
    res->y = mat->m[0][1];
    res->z = mat->m[0][2];
}

inline void vec3_up_from_matrix(T3DVec3* res, T3DMat4* mat)
{
    res->x = mat->m[1][0];
    res->y = mat->m[1][1];
    res->z = mat->m[1][2];
}

inline void vec3_forward_from_matrix(T3DVec3* res, T3DMat4* mat)
{
    res->x = mat->m[2][0];
    res->y = mat->m[2][1];
    res->z = mat->m[2][2];
}

inline void vec3_directions_from_matrix(T3DVec3* right, T3DVec3* up, T3DVec3* forward, T3DMat4* mat)
{
    vec3_right_from_matrix(right, mat);
    vec3_up_from_matrix(up, mat);
    vec3_forward_from_matrix(forward, mat);
}

#endif