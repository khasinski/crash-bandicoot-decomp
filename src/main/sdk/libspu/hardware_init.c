#include "common.h"

/* GCC_VERSION: 2.6.3 */
s32 BIOS_Printf(const char *, ...);
void _spu_writeByIO(u16 *, u32);



/* Preserve the driver reset write after enabling SPU control. */

s32 _spu_init(s32 arg0) {
    /* The hardware delay repeatedly accesses these two stack words. */
    volatile s32 delay_count;
    volatile u32 delay_value;
    s32 poll_count;
    s32 voice;
    volatile u16 *registers;

    *D_800558F4 |= 0xB0000;
    g_spu_RXX[0xC0] = 0;
    g_spu_RXX[0xC1] = 0;
    g_spu_RXX[0xD5] = 0;
    delay_value = 0xD;
    delay_count = 0;
    D_800558FC = 0;
    D_80055900 = 0;
    D_800558E0 = 0;
    if (delay_count < 0xF0) {
        do {
            delay_value *= 3;
            delay_count++;
        } while (delay_count < 0xF0);
    }
    g_spu_RXX[0xC0] = 0;
    g_spu_RXX[0xC1] = 0;
    D_800558DC = 0;
    if (g_spu_RXX[0xD7] & 0x7FF) {
loop_3:
        poll_count = D_800558DC + 1;
        D_800558DC = poll_count;
        if (poll_count >= 0x1389) {
            BIOS_Printf(D_80011660, D_80011670);
        } else if (g_spu_RXX[0xD7] & 0x7FF) {
            goto loop_3;
        }
    }
    D_80055904 = 2;
    g_spu_trans_mode = 3;
    D_8005590C = 8;
    D_80055910 = 7;
    g_spu_RXX[0xD6] = 4;
    g_spu_RXX[0xC2] = 0;
    g_spu_RXX[0xC3] = 0;
    g_spu_RXX[0xC6] = 0xFFFFU;
    g_spu_RXX[0xC7] = 0xFFFFU;
    g_spu_RXX[0xCC] = 0;
    g_spu_RXX[0xCD] = 0;
    if (arg0 == 0) {
        g_spu_RXX[0xC8] = 0;
        g_spu_RXX[0xC9] = 0;
        g_spu_RXX[0xCA] = 0;
        g_spu_RXX[0xCB] = 0;
        g_spu_RXX[0xD8] = 0;
        g_spu_RXX[0xD9] = 0;
        g_spu_RXX[0xDA] = 0;
        g_spu_RXX[0xDB] = 0;
        D_800558E0 = 0x200;
        _spu_writeByIO(D_80055920, 0x10);
        registers = g_spu_RXX;
        for (voice=0; voice<24; voice++) {
            registers[voice * 8 + 0] = 0;
            registers[voice * 8 + 1] = 0;
            registers[voice * 8 + 2] = 0x3FFF;
            registers[voice * 8 + 3] = 0x200;
            registers[voice * 8 + 4] = 0;
            registers[voice * 8 + 5] = 0;
        }
        g_spu_RXX[0xC4] |= 0xFFFFU;
        g_spu_RXX[0xC5] = (u16) (g_spu_RXX[0xC5] | 0xFF);
        delay_value = 13;
        for (delay_count = 0; delay_count < 240; delay_count++) {
            delay_value *= 3;
        }
        delay_value = 13;
        for (delay_count = 0; delay_count < 240; delay_count++) {
            delay_value *= 3;
        }
        delay_value = 13;
        for (delay_count = 0; delay_count < 240; delay_count++) {
            delay_value *= 3;
        }
        delay_value = 13;
        for (delay_count = 0; delay_count < 240; delay_count++) {
            delay_value *= 3;
        }
        g_spu_RXX[0xC6] |= 0xFFFFU;
        g_spu_RXX[0xC7] = (u16) (g_spu_RXX[0xC7] | 0xFF);
        delay_value = 13;
        for (delay_count = 0; delay_count < 240; delay_count++) {
            delay_value *= 3;
        }
        delay_value = 13;
        for (delay_count = 0; delay_count < 240; delay_count++) {
            delay_value *= 3;
        }
        delay_value = 13;
        for (delay_count = 0; delay_count < 240; delay_count++) {
            delay_value *= 3;
        }
        delay_value = 13;
        for (delay_count = 0; delay_count < 240; delay_count++) {
            delay_value *= 3;
        }
    }
    D_80055914 = 1;
    g_spu_RXX[0xD5] = 0xC000;
    D_80055918 = 0;
    D_8005591C = 0;
    return 0;
}
