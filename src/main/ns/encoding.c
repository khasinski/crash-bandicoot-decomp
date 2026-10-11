#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Character lookup and decoding for the 64-character resource-name alphabet. */

extern u8 D_80051728[];
extern s32 func_800128A4(s32, s32, s32, s32);

u8 func_80012820(s32 index)
{
    return D_80051728[index];
}

s32 func_80012834(s32 ch)
{
    s32 index;
    for (index = 0; index < 0x40; index++) {
        if (D_80051728[index] == (ch & 0xFF))
            return index;
    }
    if ((ch & 0xFF) == 0x2D)
        return 0x63;
    return -0xE;
}

s32 func_80012880(s32 a, s32 b)
{
    return func_800128A4(a, b, 0, 0);
}
