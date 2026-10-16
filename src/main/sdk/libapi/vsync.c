#include "common.h"

/* GCC_VERSION: 2.6.3 */

extern char D_80010FF0[];
extern volatile u32 *D_80053924;
extern volatile u32 *D_80053928;
extern u32 D_8005392C;
extern s32 D_80053930;
extern volatile s32 D_800549F0;

void func_8003E4E0(s32);
void func_8003E638(s32, s32);
s32 func_8003E6D4(const char *);
void func_8003E6E4(s32, s32);

s32 CORE_VSync(s32 mode)
{
    u32 status = *D_80053924;
    s32 hsync = (*D_80053928 - D_8005392C) & 0xFFFF;

    if (mode < 0) {
        return D_800549F0;
    }
    if (mode == 1) {
        return hsync;
    }
    func_8003E638(mode > 0 ? D_80053930 + (mode - 1) : D_80053930, mode > 0 ? mode - 1 : 0);
    status = *D_80053924;
    func_8003E638(D_800549F0 + 1, 1);
    if (status & 0x80000) {
        while (((status ^ *D_80053924) & 0x80000000) == 0) {
        }
    }
    D_80053930 = D_800549F0;
    D_8005392C = *D_80053928;
    return hsync;
}

void func_8003E638(s32 target, s32 count)
{
    volatile s32 timeout = count << 15;

    while (D_800549F0 < target) {
        if (--timeout == -1) {
            func_8003E6D4(D_80010FF0);
            func_8003E4E0(0);
            func_8003E6E4(3, 0);
            break;
        }
    }
}
