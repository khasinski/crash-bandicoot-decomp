#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Establish the GPU operation timeout and reset its polling counter. */
s32 VSync(s32);
s32 func_8003D730(const char *, ...);
s32 func_8003E870(s32);

extern volatile u32 *D_80054B40;
extern volatile u32 *D_80054B44;
extern volatile u32 *D_80054B4C;

extern volatile s32 D_80054B60[];

extern volatile s32 D_80054B70;

void func_80042864(void)
{
    D_80054B84 = VSync(-1) + 240;
    D_80054B88 = 0;
}

s32 func_80042898(void)
{
    if (VSync(-1) > D_80054B84 || D_80054B88++ > 0xF0000) {
        *D_80054B40;
        func_8003D730(D_80011350, (D_80054B70 - D_80054B74) & 0x3F, *D_80054B40, *D_80054B4C, *D_80054B44);
        func_8003D730(D_80011384, D_80054B60[0], D_80054B64, D_80054B68);
        D_80054B80 = func_8003E870(0);
        D_80054B74 = 0;
        D_80054B70 = D_80054B74;
        *D_80054B4C = 0x401;
        *D_80054B5C |= 0x800;
        *D_80054B40 = 0x02000000;
        *D_80054B40 = 0x01000000;
        func_8003E870(D_80054B80);
        return -1;
    }
    return 0;
}
