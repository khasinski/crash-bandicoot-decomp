#include "common.h"

/* GCC_VERSION: 2.6.3 */
extern volatile u16 *D_800558E4;

void func_80046840(s32 arg0, s16 arg1, s32 arg2) {
    /* Retail stores and reloads both delay words on the stack. */
    volatile s32 delay_count;
    volatile u32 delay_value;

    D_800558E4[0xD3] = arg1;
    delay_value = 0xD;
    delay_count = 0;
    if (delay_count < 0xF0) {
        do {
            delay_value *= 3;
            delay_count++;
        } while (delay_count < 0xF0);
    }
    delay_value = 13;
    for (delay_count = 0; delay_count < 240; delay_count++) {
        delay_value *= 3;
    }
    D_800558E4[0xD5] = (u16) (D_800558E4[0xD5] | 0x30);
    delay_value = 13;
    for (delay_count = 0; delay_count < 240; delay_count++) {
        delay_value *= 3;
    }
    delay_value = 13;
    for (delay_count = 0; delay_count < 240; delay_count++) {
        delay_value *= 3;
    }
    *D_800558F8 = (*D_800558F8 & 0xF0FFFFFF) | 0x22000000;
    *D_800558E8 = arg0;
    *D_800558EC = (arg2 << 0x10) | 0x10;
    D_80055930 = 1;
    *D_800558F0 = 0x01000200;
}
