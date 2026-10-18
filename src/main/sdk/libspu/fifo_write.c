/* GCC_VERSION: 2.6.3 */
#include "common.h"

s32 func_8003D730(const char *, ...);

extern u16 D_800558E0;
extern volatile u16 *D_800558E4;

void func_8004636C(u16 *arg0, u32 arg1)
{
    volatile s32 delay_count;
    volatile s32 delay_value;
    s32 count;
    u32 total;
    u16 *ptr;
    s32 i;
    u16 ctrl;
    u16 stat;

    total = arg1;
    stat = D_800558E4[0xD7] & 0x7FF;
    ptr = arg0;
    D_800558E4[0xD3] = D_800558E0;
    delay_value = 13;
    for (delay_count = 0; delay_count < 240; delay_count++) {
        delay_value *= 3;
    }
    while (total != 0) {
        count = total;
        if (total > 0x40) {
            count = 0x40;
        }
        for (i = 0; i < count; i += 2) {
            D_800558E4[0xD4] = *ptr++;
        }
        ctrl = D_800558E4[0xD5];
        ctrl = (ctrl & 0xFFCF) | 0x10;
        D_800558E4[0xD5] = ctrl;
        delay_value = 13;
        for (delay_count = 0; delay_count < 240; delay_count++) {
            delay_value *= 3;
        }
        D_800558DC = 0;
        while (D_800558E4[0xD7] & 0x400) {
            if (++D_800558DC > 0x1388) {
                func_8003D730(D_80011660, D_80011680);
                break;
            }
        }
        delay_value = 13;
        for (delay_count = 0; delay_count < 240; delay_count++) {
            delay_value *= 3;
        }
        delay_value = 13;
        for (delay_count = 0; delay_count < 240; delay_count++) {
            delay_value *= 3;
        }
        total -= count;
    }
    ctrl = D_800558E4[0xD5];
    ctrl &= 0xFFCF;
    D_800558E4[0xD5] = ctrl;
    D_800558DC = 0;
    while ((D_800558E4[0xD7] & 0x7FF) != stat) {
        if (++D_800558DC > 0x1388) {
            func_8003D730(D_80011660, D_80011694);
            break;
        }
    }
}
