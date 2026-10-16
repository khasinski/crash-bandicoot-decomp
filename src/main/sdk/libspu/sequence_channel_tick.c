/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
void func_8004C4D4(s16,s16);
extern u8 *D_80060418[];
void func_8004C3C8(s16 arg0, s16 arg1) {
    s16 temp_v0;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s32 temp_a1;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s0;
    s32 var_v0;
    u8 *temp_s1;

    temp_s1 = (arg1 * 0xAC) + D_80060418[arg0];
    temp_v0 = *(s16 *)(temp_s1 + 0x70);
    temp_v1 = *(s32 *)(temp_s1 + 0x88);
    temp_a1 = temp_v1 - temp_v0;
    if (temp_a1 > 0) {
        temp_v1_2 = *(s16 *)(temp_s1 + 0x6E);
        if (temp_v1_2 > 0) {
            *(s16 *)(temp_s1 + 0x6E) = (s16) (temp_v1_2 - 1);
            return;
        }
        if (temp_v1_2 == 0) {
            *(s16 *)(temp_s1 + 0x6E) = temp_v0;
            var_v0 = *(s32 *)(temp_s1 + 0x88) - 1;
            goto block_10;
        }
        *(s32 *)(temp_s1 + 0x88) = temp_a1;
        return;
    }
    if (temp_v0 >= temp_v1) {
        var_s0 = temp_v1;
        do {
loop_8:
            func_8004C4D4(arg0, arg1);
            temp_v0_2 = *(s32 *)(temp_s1 + 0x88);
            if (temp_v0_2 == 0) {
                goto loop_8;
            }
            temp_v1_3 = *(s16 *)(temp_s1 + 0x70);
            var_s0 += temp_v0_2;
        } while (var_s0 < temp_v1_3);
        var_v0 = var_s0 - temp_v1_3;
block_10:
        *(s32 *)(temp_s1 + 0x88) = var_v0;
    }
}

typedef struct {
    u8 gap00[4];
    u8 *cursor;
    u8 gap08[9];
    u8 field_11;
    u8 field_12;
    u8 gap13[0x75];
    s32 ticks;
    u8 gap8C[0x20];
} SeqChannelState;

typedef void (*EventCallback)();
s32 func_8004AEB8();
extern EventCallback D_80058360, D_80058364, D_80058368, D_8005836C, D_80058370;

void func_8004C4D4(s16 arg0, s16 arg1) {
    s32 channel_index = arg1;
    s32 sequence_index = arg0;
    SeqChannelState *state = (SeqChannelState *)D_80060418[sequence_index] + channel_index;
    s32 status;
    s32 vel;

    status = *state->cursor++;
    if (status & 0x80) {
        state->field_12 = status & 0xF;
        switch (status & 0xF0) {
        case 0x90:
            state->field_11 = 0x90;
            status = *state->cursor++;
            vel = *state->cursor++;
            state->ticks = func_8004AEB8(sequence_index, channel_index);
            D_80058360(sequence_index, channel_index, status, vel);
            break;
        case 0xB0:
            state->field_11 = 0xB0;
            status = *state->cursor++;
            status &= 0xFF;
            D_80058370(sequence_index, channel_index, status);
            break;
        case 0xC0:
            state->field_11 = 0xC0;
            status = *state->cursor++;
            status &= 0xFF;
            D_80058364(sequence_index, channel_index, status);
            break;
        case 0xE0:
            state->field_11 = 0xE0;
            state->cursor++;
            goto pitch_bend;
        case 0xF0:
            state->field_11 = 0xFF;
            state->field_12 = status & 0xF;
            status = *state->cursor++;
            D_8005836C(sequence_index, channel_index, status);
            break;
        }
    } else {
        switch (state->field_11) {
        case 0x90:
            vel = *state->cursor++;
            state->ticks = func_8004AEB8(sequence_index, channel_index);
            D_80058360(sequence_index, channel_index, status, vel);
            break;
        case 0xB0:
            D_80058370(sequence_index, channel_index, status);
            break;
        case 0xC0:
            D_80058364(sequence_index, channel_index, status);
            break;
        case 0xE0:
        pitch_bend:
            D_80058368(sequence_index, channel_index);
            break;
        case 0xFF:
            D_8005836C(sequence_index, channel_index, status);
            break;
        }
    }
}

