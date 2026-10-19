/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"

s32 SpuVmVSetUp(s16,s16);
typedef struct { s16 value; u8 pad[50]; } VoiceWord;
extern VoiceWord D_800572B4[];
extern VoiceWord D_800572BA[];
extern VoiceWord D_800572BE[];
extern VoiceWord D_800572C0[];
extern VoiceWord D_800572C2[];
typedef struct { s16 left; s16 right; u8 pad[12]; } VoiceVol;

extern VoiceVol g_midi_seq_table[];
extern u8 *D_8005CFDC;


s32 SpuVmSetVol(s16 arg0, s16 arg1, s16 arg2, s32 arg3, u16 arg4) {
    s16 temp_a0_2;
    s32 var_s6;
    u8 var_t2;
    u32 temp_lo;
    u32 temp_lo_2;
    u32 var_a1;
    u32 var_t1;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u32 temp_v1_5;
    s32 master_volume;
    SequenceState *temp_s2;
    u8 r;
    u32 r2;

    var_s6 = 0;
    temp_s2 = g_ss_score_table[arg0 & 255] + (((u32)(arg0 << 0x10)) >> 24);
    SpuVmVSetUp(arg1, arg2);
    D_8005E56E = arg0;
    if (arg4 == 0) {
        arg4 = 1;
    }
    if (!(arg3 & 0xFFFF)) {
        arg3 = 1;
    }
    for (var_t2 = 0; var_t2 < gp_spawn_count; var_t2++) {
        if ((D_800572BA[var_t2].value == arg0) && (D_800572BE[var_t2].value == arg2) && (D_800572C2[var_t2].value == arg1)) {
            if ((temp_s2->gains[temp_s2->field_12] != (arg3 & 0xFFFF)) && (temp_s2->gains[temp_s2->field_12] == 0)) {
                temp_s2->gains[temp_s2->field_12] = 1;
            }
            temp_lo = (D_800572B4[var_t2].value * (arg3 & 0xFFFF)) / 127;
            master_volume = D_8005CFDC[0x18];
            temp_lo_2 = ((s32)temp_lo * ((master_volume << 14) - master_volume)) / 16129;
            temp_lo = temp_lo_2 * D_8005CFCC[arg2 * 16 + 1];
            temp_a0_2 = D_800572C0[var_t2].value;
            temp_lo = ((u32)temp_lo * g_ns_vpage_pool[((arg2 * 16 + temp_a0_2) << 5) + 2]) / 16129U;
            temp_lo_2 = (u32) (temp_lo * temp_s2->field_74) / 127U;
            var_t1 = (u32) (temp_lo * temp_s2->field_76) / 127U;
            temp_v1_3 = g_ns_vpage_pool[(temp_a0_2 << 5) + 3];
            if (temp_v1_3 < 0x40U) {
                var_t1 = (u32) (var_t1 * temp_v1_3) / 63U;
                var_a1 = temp_lo_2;
            } else {
                var_a1 = (u32) (temp_lo_2 * (0x7F - temp_v1_3)) / 63U;
            }
            temp_v1_4 = D_8005CFCC[D_800572BE[var_t2].value * 16 + 4];
            if (temp_v1_4 < 0x40U) {
                var_t1 = (u32) (var_t1 * temp_v1_4) / 63U;
            } else {
                var_a1 = (u32) (var_a1 * (0x7F - temp_v1_4)) / 63U;
            }
            r = var_t2 * 12;
            temp_lo_2 = (arg4 & 0x7F00);
            temp_lo_2 |= arg4;
            temp_v1_5 = temp_lo_2 & 0xFF;
            r2 = (temp_v1_5 < 0x40U) | (r & 0x7F00);
            r2 |= (r2 & 0x7F00) | (r2 & 0x3F00) | (r2 & 0x1F00) | (r2 & 0x0F00) | (r2 & 0x0700) | (r2 & 0x0300);
            if (r2) {
                var_t1 = (u32) (var_t1 * temp_v1_5) / 63U;
            } else {
                var_a1 = (u32) (var_a1 * (0x7F - temp_v1_5)) / 63U;
            }
            if (D_800583F8 == 1) {
                if (var_a1 < var_t1) {
                    var_a1 = var_t1;
                } else {
                    var_t1 = var_a1;
                }
            }
            var_a1 = (var_a1 * var_a1) / 16383U;
            var_t1 = (var_t1 * var_t1) / 16383U;
            *(s16 *)((u32)&g_midi_seq_table[0].left + var_t2 * 16) = var_a1;
            *(s16 *)((u32)&g_midi_seq_table[0].right + var_t2 * 16) = var_t1;
            var_s6 += 1;
            g_card_ev_table[var_t2] = g_card_ev_table[var_t2] | 3;
        }
    }
    return var_s6;
}
