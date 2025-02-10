#include "game_math.h"







i8 i8_bit_clamp(i8 x, i8 min, i8 max)
{
    i8 belowMin = (x - min) >> 7;
    i8 aboveMax = (max - x) >> 7;
    return (aboveMax & max) | (~aboveMax & ((belowMin & min) | (~belowMin & x)));
}


