/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

typedef struct {
    u8 gap0[4];
    u32 field_4;
    u32 field_8;
    u32 field_C;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u8 field_14;
    u8 field_15;
    u8 field_16;
    u8 field_17[16];
    u8 field_27;
    u8 field_28;
    u8 field_29;
    u8 field_2A;
    u8 field_2B;
    u8 field_2C[16];
    u8 gap3C[12];
    s16 field_48;
    s16 field_4A;
    s16 field_4C;
    s16 gains[16];
    s16 field_6E;
    u16 field_70;
    u16 field_72;
    u16 field_74;
    u16 field_76;
    s16 field_78;
    s16 field_7A;
    u32 field_7C;
    u32 field_80;
    u32 field_84;
    u32 field_88;
    u32 field_8C;
    s32 field_90;
    u8 gap94[0xAC - 0x94];
} SequenceState;

void func_80050060(s16);
extern SequenceState *D_80060418[];

void func_8004C7CC(s16 arg0, s16 arg1) {
    s32 var_t0;
    SequenceState *temp_s0;

    temp_s0 = &D_80060418[arg0][arg1];
    D_80060418[arg0][arg1].field_90 &= ~1;
    D_80060418[arg0][arg1].field_90 &= ~2;
    D_80060418[arg0][arg1].field_90 &= ~8;
    D_80060418[arg0][arg1].field_90 |= 4;
    func_80050060((arg1 << 8) | arg0);
    temp_s0->field_2B = 0;
    temp_s0->field_80 = 0;
    temp_s0->field_27 = 0;
    temp_s0->field_13 = 0;
    temp_s0->field_14 = 0;
    temp_s0->field_29 = 0;
    temp_s0->field_15 = 0;
    temp_s0->field_16 = 0;
    temp_s0->field_2A = 0;
    temp_s0->field_12 = 0;
    temp_s0->field_48 = 0;
    temp_s0->field_27 = 0;
    temp_s0->field_28 = 0;
    temp_s0->field_10 = 0;
    temp_s0->field_11 = 0;
    temp_s0->field_88 = temp_s0->field_7C;
    temp_s0->field_8C = temp_s0->field_84;
    temp_s0->field_70 = temp_s0->field_72;
    temp_s0->field_4 = temp_s0->field_8;
    temp_s0->field_C = temp_s0->field_8;
    for (var_t0 = 0; var_t0 < 0x10; var_t0++) {
        temp_s0->field_2C[var_t0] = var_t0;
        temp_s0->field_17[var_t0] = 0x40;
        temp_s0->gains[var_t0] = 0x7F;
    }
    temp_s0->field_78 = 0x7F;
    temp_s0->field_7A = 0x7F;
}
