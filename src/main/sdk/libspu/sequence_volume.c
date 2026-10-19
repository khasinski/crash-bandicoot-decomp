/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"

/* Known fields and the 0xAC stride are recovered from retail loads/stores. */
typedef char SoundStateStride[(sizeof(SequenceState) == 0xAC) ? 1 : -1];
typedef struct { u8 bytes[0x19]; } Master;
extern u8 D_800572B4[];
extern u8 D_800572BA[];
extern u8 D_800572C0[];
extern u8 g_midi_seq_table[];
typedef struct { s16 program; u8 rest[50]; } ProgramVoice;
typedef struct { u8 pan; u8 rest[51]; } PanVoice;
extern ProgramVoice D_800572BE[];
extern PanVoice D_800572B6[];

extern Master *D_8005CFDC;


s16 SpuVmSetSeqVol(s16 arg0, u16 arg1, u16 arg2, s16 arg3) {
    s16 temp_a1_2;
    s16 left_result, right_result;
    s16 var_t3;
    s32 temp_a1;
    s32 scaled_velocity;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_3;
    u32 temp_lo;
    u32 temp_lo_2;
    u32 temp_lo_3;
    u16 var_a1;
    u16 var_a3;
    u8 temp_a0;
    u8 temp_a0_2;
    u8 temp_v1_2;
    SequenceState *temp_t2;

    temp_t2 = g_ss_score_table[arg0 & 0xFF] + ((u32) (arg0 << 0x10) >> 0x18);
    D_8005E56E = arg0;
    *(u16 *)(void *)&temp_t2->field_74 = arg1;
    temp_t2->field_76 = arg2;
    if ((u16) *(u16 *)(void *)&temp_t2->field_74 >= 0x80U) {
        *(u16 *)(void *)&temp_t2->field_74 = 0x7FU;
    }
    if ((u16) temp_t2->field_76 >= 0x80U) {
        temp_t2->field_76 = 0x7FU;
    }
    if (arg3 == 1) {
        var_t3 = 0;
        if (gp_spawn_count != 0) {
            u32 seq_key = arg0 & 0xFFFF;
            do {
                s32 volume_max = 127;
                s32 volume_square = 16129;
                s32 pan_max = 63;

                s16 *left_shadow = (s16 *)g_midi_seq_table;
                s16 *right_shadow = left_shadow + 1;
                temp_a1 = var_t3 * 0x34;
                if (*(u16 *)(D_800572BA + temp_a1) == seq_key) {
                    scaled_velocity = ((s32) (*(s16 *)(D_800572B4 + temp_a1) * temp_t2->gains[temp_t2->field_12]) / volume_max);
                    scaled_velocity = (s32)(D_8005CFDC->bytes[0x18] * (((u32)scaled_velocity << 14) - (u32)scaled_velocity)) / volume_square;
                    temp_v1 = D_800572BE[var_t3].program * 0x10;
                    scaled_velocity *= D_8005CFCC[temp_v1 + 1];
                    temp_a1_2 = *(s16 *)(D_800572C0 + temp_a1);
                    temp_lo = (u32)(scaled_velocity * g_ns_vpage_pool[((temp_v1 + temp_a1_2) << 5) + 2]) / (u32)volume_square;
                    temp_lo_2 = (u32) (temp_lo * *(u16 *)(void *)&temp_t2->field_74) / (u32)volume_max;
                    temp_lo_3 = (u32) (temp_lo * temp_t2->field_76) / (u32)volume_max;
                    temp_v1_2 = g_ns_vpage_pool[(temp_a1_2 << 5) + 3];
                    if (temp_v1_2 < 0x40U) {
                        var_a1 = temp_lo_2;
                        var_a3 = (u32) (temp_lo_3 * temp_v1_2) / (u32)pan_max;
                    } else {
                        var_a3 = temp_lo_3;
                        var_a1 = (u32) (temp_lo_2 * (volume_max - temp_v1_2)) / (u32)pan_max;
                    }
                    temp_a0 = D_8005CFCC[(D_800572BE[var_t3].program * 16) + 4];
                    if (temp_a0 < 0x40U) {
                        var_a3 = (u32) ((s32) (var_a3 * temp_a0) / pan_max);
                    } else {
                        var_a1 = (u32) ((s32) (var_a1 * (volume_max - temp_a0)) / pan_max);
                    }
                    temp_a0_2 = D_800572B6[var_t3].pan;
                    if (temp_a0_2 < 0x40U) {
                        var_a3 = (u32) ((s32) (var_a3 * temp_a0_2) / pan_max);
                    } else {
                        var_a1 = (u32) ((s32) (var_a1 * (volume_max - temp_a0_2)) / pan_max);
                    }
                    if (D_800583F8 == 1) {
                        if (var_a1 < var_a3) {
                            var_a1 = var_a3;
                        } else {
                            var_a3 = var_a1;
                        }
                    }
                    temp_v0 = var_a3;
                    temp_v1_3 = var_t3 * 0x10;
                    left_result = (s16) ((s32) ((u32)var_a1 * var_a1) / 16383);
                    right_result = (s16) ((s32) (temp_v0 * temp_v0) / 16383);
                    *(s16 *)(temp_v1_3 + (u32)left_shadow) = left_result;
                    *(s16 *)(temp_v1_3 + (u32)right_shadow) = right_result;
                    g_card_ev_table[var_t3] = g_card_ev_table[var_t3] | 3;
                }
                var_t3++;
            } while (var_t3 < (s32) gp_spawn_count);
        }
    }
    return D_8005E56E;
}
