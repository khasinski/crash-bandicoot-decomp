#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* The two retail generator states both start at one. */
s32 D_800564D8 = 1;
s32 D_800564DC = 1;

/* Advance the corresponding LCG state, normalise through unsigned division
 * and reduction, then take a signed remainder against the supplied bound.
 */

s32 func_8002F6B0(s32 bound)
{
    s32 value;
    if (bound != 0) {
        D_800564D8 = D_800564D8 * 0x41C64E6D + 0x3039;
        value = ((u32)D_800564D8 / 15) % 0x07FFFFFF;
        if (value < 0) {
            value = -value;
        }
        return value % bound;
    }
    return 0;
}

void func_8002F75C(void)
{
    D_800564D8 = 0x3039;
}

void func_8002F76C(s32 value)
{
    D_800564D8 = value;
}

s32 func_8002F778(s32 bound)
{
    s32 value;
    if (bound != 0) {
        D_800564DC = D_800564DC * 0x41C64E6D + 0x3039;
        value = ((u32)D_800564DC / 15) % 0x07FFFFFF;
        if (value < 0) {
            value = -value;
        }
        return value % bound;
    }
    return 0;
}

void func_8002F824(void)
{
    D_800564DC = 0x3039;
}

void func_8002F834(s32 value)
{
    D_800564DC = value;
}
