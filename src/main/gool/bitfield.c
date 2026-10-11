#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Sign-extend the low bits of a GOOL operand. */

s32 func_8001FB20(s32 value, s32 bits)
{
    s32 shift = 0x20 - bits;
    return (s32)((u32)value << shift) >> shift;
}
