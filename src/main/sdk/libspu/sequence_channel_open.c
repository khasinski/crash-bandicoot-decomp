/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */

#include "common.h"
s32 BIOS_Printf(const char *, ...);
s32 _SsReadDeltaValue(s16, s16);


/* A quarter of the shared 60-tick divisor is used for rounding below. */
static __inline__ u32 clock_divisor(u32 ticks) {
    return ticks << 2;
}

s32 _SsInitSoundSep(s16 arg0, s16 arg1, s16 arg2, u8 *arg3) {
    s32 fifteen_ticks;
    u32 tempo_mid;
    s32 temp_lo;
    s32 temp_s2;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_s1;
    s32 var_a1;
    u32 temp_lo_2;
    u32 temp_lo_3;
    u32 temp_lo_4;
    u32 temp_a2;
    u32 temp_a3;
    u8 temp_v1;
    u8 *temp_a0;
    /* The parser cursor and clock divisor occupy separate phases. */
    union {
        u8 *bytes;
        u32 divisor;
    } operand;
    SequenceState *temp_s0;
    SequenceState *temp_v0;
    u8 *temp_v1_2;
    u8 *var_v1;

    temp_s0 = g_ss_score_table[arg0] + arg1;
    var_s1 = 0;
    temp_s0->field_10 = 0;
    temp_s0->field_11 = 0;
    temp_s0->field_12 = 0;
    temp_s0->field_13 = 0;
    temp_s0->field_14 = 0;
    temp_s0->field_15 = 0;
    temp_s0->field_16 = 0;
    temp_s0->field_27 = 0;
    temp_s0->field_28 = 0;
    temp_s0->field_29 = 0;
    temp_s0->field_2A = 0;
    temp_s0->field_2B = 0;
    temp_s0->field_48 = 0;
    temp_s0->field_6E = 1;
    temp_s0->field_4A = 0;
    temp_s0->field_4C = arg2;
    temp_s0->field_72 = 0U;
    temp_s0->field_7C = 0;
    temp_s0->field_80 = 0;
    temp_s0->field_84 = 0;
    temp_s0->field_88 = 0;
    temp_s0->field_A8 = 0x7F;
    temp_s0->field_AA = 0;
    var_a1 = 0;
    var_v1 = (u8 *)temp_s0;
    do {
        temp_v0 = (SequenceState *)((u32)temp_s0 + var_a1);
        temp_v0->field_17[0] = 0x40;
        temp_v0->field_2C[0] = var_a1;
        ((s16 *)var_v1)[0x27] = 0x7F;
        var_a1 += 1;
        var_v1 += 2;
    } while (var_a1 < 0x10);
    temp_s0->field_4 = arg3;
    if ((arg1 << 0x10) == 0) {
        temp_v1 = arg3[0x0];
        switch (temp_v1) {
        case 0x53:
        case 0x70:
            temp_s0->field_4 = (u8 *) (arg3 + 6);
            if (arg3[0x5] != 0) {
                BIOS_Printf(g_jtbl_ss_meta_event);
                return -1;
            }
            temp_s0->field_4 = (u8 *) (arg3 + 8);
            var_s1 += 8;
            goto block_9;
        }
        goto block_9;
    }
    temp_s0->field_4 = (u8 *) (arg3 + 2);
    var_s1 += 2;
block_9:
    temp_v1_2 = temp_s0->field_4;
    temp_s0->field_4 = temp_v1_2 + 1;
    temp_a2 = temp_v1_2[0];
    temp_s0->field_4 = temp_v1_2 + 2;
    temp_s0->field_4A = temp_v1_2[1] | (temp_a2 << 8);
    temp_a0 = temp_s0->field_4;
    temp_s0->field_4 = temp_a0 + 1;
    temp_a3 = temp_a0[0];
    temp_s0->field_4 = temp_a0 + 2;
    tempo_mid = temp_a0[1];
    temp_s0->field_4 = (u8 *) (temp_a0 + 3);
    temp_v0_2 = (temp_a3 << 16) | (tempo_mid << 8) | temp_a0[0x2];
    temp_lo = 0x03938700 / temp_v0_2;
    temp_s0->field_84 = temp_v0_2;
    var_s1 += 5;
    if ((s32) ((u32) temp_v0_2 >> 1) < (0x03938700 % temp_v0_2)) {
        temp_s0->field_84 = (s32) (temp_lo + 1);
    } else {
        temp_s0->field_84 = temp_lo;
    }
    operand.bytes = temp_s0->field_4;
    temp_s0->field_8C = (s32) temp_s0->field_84;
    temp_s0->field_4 = (u8 *) (operand.bytes + 3);
    temp_a2 = operand.bytes[0x2];
    temp_s0->field_4 = operand.bytes + 4;
    temp_v1 = operand.bytes[3];
    temp_s0->field_4 = (u8 *) (operand.bytes + 5);
    temp_a3 = operand.bytes[0x4];
    temp_s0->field_4 = (u8 *) (operand.bytes + 6);
    temp_s2 = (temp_a2 << 0x18) + (temp_v1 << 16) + (temp_a3 << 8) + operand.bytes[0x5];
    temp_v0_3 = _SsReadDeltaValue(arg0, arg1);
    temp_v1_2 = temp_s0->field_4;
    var_s1 += 6;
    temp_lo_2 = temp_s0->field_4A * temp_s0->field_84;
    temp_s0->field_7C = temp_v0_3;
    temp_a0 = temp_s0->field_4;
    temp_s0->field_88 = temp_v0_3;
    temp_s0->field_C = temp_a0;
    fifteen_ticks = g_spawns_base << 4;
    fifteen_ticks -= g_spawns_base;
    operand.divisor = clock_divisor(fifteen_ticks);
    temp_s0->field_8 = temp_v1_2;
    if ((u32) (temp_lo_2 * 0xA) < operand.divisor) {
        temp_lo_3 = (u32) (g_spawns_base * 0x258) / temp_lo_2;
        temp_s0->field_6E = (s16) temp_lo_3;
        temp_s0->field_70 = (u16) temp_lo_3;
    } else {
        temp_lo_4 = (u32) (temp_s0->field_4A * temp_s0->field_84 * 0xA) / operand.divisor;
        temp_s0->field_6E = -1;
        temp_s0->field_70 = (u16) temp_lo_4;
        if ((u32) (fifteen_ticks * 2) < (u32) ((u32) (temp_s0->field_4A * temp_s0->field_84 * 0xA) % operand.divisor)) {
            temp_s0->field_70 = (u16) (temp_lo_4 + 1);
        }
    }
    temp_s0->field_72 = (u16) temp_s0->field_70;
    return var_s1 + temp_s2;
}
