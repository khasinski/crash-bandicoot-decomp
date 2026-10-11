/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
extern s32 D_8005FF4C;
extern u8 *D_80060418[];

void func_8004CDCC(s16 arg0, s16 arg1) {
    s32 sequence_shift;
    u32 table_base;
    s32 temp_t0;
    u8 **temp_a2;
    s32 temp_v0_4;
    s32 var_v0_2;
    u32 temp_a0;
    u32 temp_a0_2;
    u32 temp_lo;
    u32 temp_v0;
    u32 temp_v1;
    u32 var_v0;
    u8 *temp_a1;
    u8 *temp_a3;
    u8 *temp_v0_5;

    temp_a3 = (arg1 * 0xAC) + D_80060418[(s16)arg0];
    temp_t0 = *(s16 *)(temp_a3 + 0x44);
    temp_v0 = *(u32 *)(temp_a3 + 0xA0) - 1;
    *(u32 *)(temp_a3 + 0xA0) = temp_v0;
    if (temp_t0 > 0) {
        if ((temp_v0 % (u32) temp_t0) == 0) {
            temp_v1 = *(u32 *)(temp_a3 + 0x8C);
            temp_a0 = *(u32 *)(temp_a3 + 0xA4);
            if (temp_a0 < temp_v1) {
                var_v0 = temp_v1 - 1;
                goto update_tempo;
            }
            if (temp_v1 < temp_a0) {
                var_v0 = temp_v1 + 1;
update_tempo:
                *(u32 *)(temp_a3 + 0x8C) = var_v0;
            }
            goto block_11;
        }
    } else {
        temp_v1 = *(u32 *)(temp_a3 + 0x8C);
        temp_a0_2 = *(u32 *)(temp_a3 + 0xA4);
        if (temp_a0_2 < temp_v1) {
            *(u32 *)(temp_a3 + 0x8C) = temp_t0 + temp_v1;
            var_v0_2 = *(u32 *)(temp_a3 + 0x8C) < temp_a0_2;
            goto block_9;
        }
        if (temp_v1 < temp_a0_2) {
            *(u32 *)(temp_a3 + 0x8C) = temp_v1 - temp_t0;
            temp_a0_2 = *(u32 *)(temp_a3 + 0xA4);
            var_v0_2 = temp_a0_2 < *(u32 *)(temp_a3 + 0x8C);
block_9:
            if (var_v0_2 != 0) {
                *(u32 *)(temp_a3 + 0x8C) = temp_a0_2;
            }
        }
block_11:
        temp_lo = (u32) (*(s16 *)(temp_a3 + 0x4A) * *(u32 *)(temp_a3 + 0x8C) * 0xA) / (u32) (D_8005FF4C * 0x3C);
        *(s16 *)(temp_a3 + 0x70) = (s16) temp_lo;
        if ((s32)(temp_lo << 16) <= 0) {
            *(s16 *)(temp_a3 + 0x70) = 1;
        }
        if ((*(u32 *)(temp_a3 + 0xA0) == 0) || (*(u32 *)(temp_a3 + 0x8C) == *(u32 *)(temp_a3 + 0xA4))) {
            sequence_shift = (u32)(u16)arg0 << 16;
            table_base = (u32)D_80060418;
            temp_a2 = (u8 **)(table_base + (sequence_shift >> 14));
            temp_v0_4 = arg1 * 0xAC;
            temp_a1 = temp_v0_4 + *temp_a2;
            *(u32 *)(temp_a1 + 0x90) = (s32) (*(u32 *)(temp_a1 + 0x90) & ~0x40);
            temp_v0_5 = temp_v0_4 + *temp_a2;
            *(u32 *)(temp_v0_5 + 0x90) = (s32) (*(u32 *)(temp_v0_5 + 0x90) & ~0x80);
        }
    }
}
