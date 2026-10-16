#include "common.h"

/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */

extern u32 *D_800566AC;
extern s32 *D_800566F4;
extern u32 *D_8005670C;
extern u32 D_80052CF4[];

s32 func_8002D638(void)
{
    s32 i;

    D_800566F4 = (s32 *)0x1F800100;
    D_800566AC = (u32 *)0x1F800180;
    D_8005670C = (u32 *)0x1F800380;
    for (i = 0; i < 32; i++) {
        D_8005670C[i] = D_80052CF4[i];
    }
    return -255;
}

s32 func_8002D694(void)
{
    return -255;
}

