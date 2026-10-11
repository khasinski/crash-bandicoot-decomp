/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
/* CC1_FLAGS: -O2 -fno-strength-reduce */
#include "common.h"
void func_80050060(s16);
extern u8 *D_80060418[];
void func_8004C7CC(s16 arg0, s16 arg1) {
    u8 **temp_t0;
    s32 temp_a1;
    s32 pan;
    s32 gain;
    s32 sequence_index;
    u32 table_base;
    s32 temp_v1;
    s32 var_t0;
    u8 *temp_a2;
    u8 *temp_a2_2;
    u8 *temp_s0;
    u8 *temp_v1_2;
    u8 *var_a3;
    u8 *var_t1;

    sequence_index = arg0;
    table_base = (u32)D_80060418;
    temp_t0 = (u8 **)(table_base + sequence_index * 4);
    temp_v1 = arg1 * 0xAC;
    temp_s0 = temp_v1 + *temp_t0;
    *(s32 *)(temp_s0 + 0x90) = (s32) (*(s32 *)(temp_s0 + 0x90) & ~1);
    temp_a2 = temp_v1 + *temp_t0;
    *(s32 *)(temp_a2 + 0x90) = (s32) (*(s32 *)(temp_a2 + 0x90) & ~2);
    temp_a2_2 = temp_v1 + *temp_t0;
    *(s32 *)(temp_a2_2 + 0x90) = (s32) (*(s32 *)(temp_a2_2 + 0x90) & ~8);
    temp_v1_2 = temp_v1 + *temp_t0;
    temp_a1 = arg1 << 8;
    *(s32 *)(temp_v1_2 + 0x90) = (s32) (*(s32 *)(temp_v1_2 + 0x90) | 4);
    func_80050060(temp_a1 | arg0);
    *(u8 *)(temp_s0 + 0x2B) = 0;
    *(u32 *)(temp_s0 + 0x80) = 0;
    *(u8 *)(temp_s0 + 0x27) = 0;
    *(u8 *)(temp_s0 + 0x13) = 0;
    *(u8 *)(temp_s0 + 0x14) = 0;
    *(u8 *)(temp_s0 + 0x29) = 0;
    *(u8 *)(temp_s0 + 0x15) = 0;
    *(u8 *)(temp_s0 + 0x16) = 0;
    *(u8 *)(temp_s0 + 0x2A) = 0;
    *(u8 *)(temp_s0 + 0x12) = 0;
    *(s16 *)(temp_s0 + 0x48) = 0;
    *(u8 *)(temp_s0 + 0x27) = 0;
    *(u8 *)(temp_s0 + 0x28) = 0;
    *(u8 *)(temp_s0 + 0x10) = 0;
    *(u8 *)(temp_s0 + 0x11) = 0;
    var_t0 = 0;
    pan = 0x40;
    gain = 0x7F;
    var_t1 = temp_s0;
    var_a3 = temp_s0;
    *(u32 *)(temp_s0 + 0x88) = (s32) *(u32 *)(temp_s0 + 0x7C);
    *(u32 *)(temp_s0 + 0x8C) = (s32) *(u32 *)(temp_s0 + 0x84);
    *(u16 *)(temp_s0 + 0x70) = (u16) *(u16 *)(temp_s0 + 0x72);
    *(u32 *)(temp_s0 + 0x4) = (s32) *(u32 *)(temp_s0 + 0x8);
    *(u32 *)(temp_s0 + 0xC) = (s32) *(u32 *)(temp_s0 + 0x8);
    do {
        *(u8 *)(var_a3 + 0x2C) = var_t0;
        *(u8 *)(var_a3 + 0x17) = pan;
        *(s16 *)(var_t1 + 0x4E) = gain;
        var_t1 += 2;
        var_t0 += 1;
        var_a3 += 1;
    } while (var_t0 < 0x10);
    *(s16 *)(temp_s0 + 0x78) = 0x7F;
    *(s16 *)(temp_s0 + 0x7A) = 0x7F;
}
