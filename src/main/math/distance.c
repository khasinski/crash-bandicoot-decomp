#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Absolute difference of two signed values, preserving the retail subtraction order. */

s32 func_8002F840(s32 a, s32 b)
{
    s32 delta = a - b;

    if (delta < 0)
        delta = b - a;
    return delta;
}
