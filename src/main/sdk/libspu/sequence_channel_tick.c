/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

void _SsSeqPlay(s16 arg0, s16 arg1) {
    s16 temp_v0;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s32 temp_a1;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s0;
    s32 var_v0;
    SequenceState *temp_s1;

    temp_s1 = &g_ss_score_table[arg0][arg1];
    temp_v0 = temp_s1->field_70;
    temp_v1 = temp_s1->field_88;
    temp_a1 = temp_v1 - temp_v0;
    if (temp_a1 > 0) {
        temp_v1_2 = temp_s1->field_6E;
        if (temp_v1_2 > 0) {
            temp_s1->field_6E = (s16) (temp_v1_2 - 1);
            return;
        }
        if (temp_v1_2 == 0) {
            temp_s1->field_6E = temp_v0;
            var_v0 = temp_s1->field_88 - 1;
            goto block_10;
        }
        temp_s1->field_88 = temp_a1;
        return;
    }
    if (temp_v0 >= temp_v1) {
        var_s0 = temp_v1;
        do {
loop_8:
            _SsSndTempo(arg0, arg1);
            temp_v0_2 = temp_s1->field_88;
            if (temp_v0_2 == 0) {
                goto loop_8;
            }
            temp_v1_3 = temp_s1->field_70;
            var_s0 += temp_v0_2;
        } while (var_s0 < temp_v1_3);
        var_v0 = var_s0 - temp_v1_3;
block_10:
        temp_s1->field_88 = var_v0;
    }
}

typedef void (*EventCallback)();

void _SsSndTempo(s16 arg0, s16 arg1) {
    s32 channel_index = arg1;
    s32 sequence_index = arg0;
    SequenceState *state = (SequenceState *)g_ss_score_table[sequence_index] + channel_index;
    s32 status;
    s32 vel;

    status = *state->field_4++;
    if (status & 0x80) {
        state->field_12 = status & 0xF;
        switch (status & 0xF0) {
        case 0x90:
            state->field_11 = 0x90;
            status = *state->field_4++;
            vel = *state->field_4++;
            state->field_88 = _SsReadDeltaValue(sequence_index, channel_index);
            g_Snd_FnTable[0](sequence_index, channel_index, status, vel);
            break;
        case 0xB0:
            state->field_11 = 0xB0;
            status = *state->field_4++;
            status &= 0xFF;
            g_ss_fn_control_change(sequence_index, channel_index, status);
            break;
        case 0xC0:
            state->field_11 = 0xC0;
            status = *state->field_4++;
            status &= 0xFF;
            g_ss_fn_note_off(sequence_index, channel_index, status);
            break;
        case 0xE0:
            state->field_11 = 0xE0;
            state->field_4++;
            goto pitch_bend;
        case 0xF0:
            state->field_11 = 0xFF;
            state->field_12 = status & 0xF;
            status = *state->field_4++;
            g_ss_fn_meta_event(sequence_index, channel_index, status);
            break;
        }
    } else {
        switch (state->field_11) {
        case 0x90:
            vel = *state->field_4++;
            state->field_88 = _SsReadDeltaValue(sequence_index, channel_index);
            g_Snd_FnTable[0](sequence_index, channel_index, status, vel);
            break;
        case 0xB0:
            g_ss_fn_control_change(sequence_index, channel_index, status);
            break;
        case 0xC0:
            g_ss_fn_note_off(sequence_index, channel_index, status);
            break;
        case 0xE0:
        pitch_bend:
            g_ss_fn_pitch_bend(sequence_index, channel_index);
            break;
        case 0xFF:
            g_ss_fn_meta_event(sequence_index, channel_index, status);
            break;
        }
    }
}

