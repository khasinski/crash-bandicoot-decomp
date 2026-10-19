/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"


void _SsSndSetRit(s16 arg0, s16 arg1) {
    s32 temp_t0;
    s32 var_v0_2;
    u32 temp_a0;
    u32 temp_a0_2;
    u32 temp_lo;
    u32 temp_v0;
    u32 temp_v1;
    u32 var_v0;
    SequenceState *temp_a3;

    temp_a3 = &g_ss_score_table[(s16)arg0][arg1];
    temp_t0 = temp_a3->field_44;
    temp_v0 = temp_a3->field_A0 - 1;
    temp_a3->field_A0 = temp_v0;
    if (temp_t0 > 0) {
        if ((temp_v0 % (u32) temp_t0) == 0) {
            temp_v1 = temp_a3->field_8C;
            temp_a0 = temp_a3->field_A4;
            if (temp_a0 < temp_v1) {
                var_v0 = temp_v1 - 1;
                goto update_tempo;
            }
            if (temp_v1 < temp_a0) {
                var_v0 = temp_v1 + 1;
update_tempo:
                temp_a3->field_8C = var_v0;
            }
            goto block_11;
        }
    } else {
        temp_v1 = temp_a3->field_8C;
        temp_a0_2 = temp_a3->field_A4;
        if (temp_a0_2 < temp_v1) {
            temp_a3->field_8C = temp_t0 + temp_v1;
            var_v0_2 = temp_a3->field_8C < temp_a0_2;
            goto block_9;
        }
        if (temp_v1 < temp_a0_2) {
            temp_a3->field_8C = temp_v1 - temp_t0;
            temp_a0_2 = temp_a3->field_A4;
            var_v0_2 = temp_a0_2 < temp_a3->field_8C;
block_9:
            if (var_v0_2 != 0) {
                temp_a3->field_8C = temp_a0_2;
            }
        }
block_11:
        temp_lo = (u32) (temp_a3->field_4A * temp_a3->field_8C * 0xA) / (u32) (g_spawns_base * 0x3C);
        temp_a3->field_70 = (s16) temp_lo;
        if ((s32)(temp_lo << 16) <= 0) {
            temp_a3->field_70 = 1;
        }
        if ((temp_a3->field_A0 == 0) || (temp_a3->field_8C == temp_a3->field_A4)) {
            g_ss_score_table[arg0][arg1].field_90 &= ~0x40;
            g_ss_score_table[arg0][arg1].field_90 &= ~0x80;
        }
    }
}
