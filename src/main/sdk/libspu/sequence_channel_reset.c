/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"


void SpuVmSeqKeyOff(s16);

void _SsSndStop(s16 arg0, s16 arg1) {
    s32 var_t0;
    SequenceState *temp_s0;

    temp_s0 = &g_ss_score_table[arg0][arg1];
    g_ss_score_table[arg0][arg1].field_90 &= ~1;
    g_ss_score_table[arg0][arg1].field_90 &= ~2;
    g_ss_score_table[arg0][arg1].field_90 &= ~8;
    g_ss_score_table[arg0][arg1].field_90 |= 4;
    SpuVmSeqKeyOff((arg1 << 8) | arg0);
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
