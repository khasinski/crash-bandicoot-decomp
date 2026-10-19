#include "common.h"

/* GCC_VERSION: 2.6.3 */


void ChangeClearPAD(s32);
void v_wait(s32, s32);
s32 puts(const char *);
void ChangeClearRCnt(s32, s32);

s32 VSync(s32 mode)
{
    u32 status = *D_80053924;
    s32 hsync = (*D_80053928 - D_8005392C) & 0xFFFF;

    if (mode < 0) {
        return D_800549F0;
    }
    if (mode == 1) {
        return hsync;
    }
    v_wait(mode > 0 ? D_80053930 + (mode - 1) : D_80053930, mode > 0 ? mode - 1 : 0);
    status = *D_80053924;
    v_wait(D_800549F0 + 1, 1);
    if (status & 0x80000) {
        while (((status ^ *D_80053924) & 0x80000000) == 0) {
        }
    }
    D_80053930 = D_800549F0;
    D_8005392C = *D_80053928;
    return hsync;
}

void v_wait(s32 target, s32 count)
{
    volatile s32 timeout = count << 15;

    while (D_800549F0 < target) {
        if (--timeout == -1) {
            puts(D_80010FF0);
            ChangeClearPAD(0);
            ChangeClearRCnt(3, 0);
            break;
        }
    }
}
