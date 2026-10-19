/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"



s32 _SsReadDeltaValue(s16, s16);
void _SsSndNextSep(s16, s16);
void SpuVmSeqKeyOff(s16);

static __inline__ u32 clock_divisor(u32 ticks) {
    return ticks << 2;
}

void _SsGetMetaEvent(s16 arg0, s16 arg1, u8 arg2) {
    s32 fifteen_ticks;
    u32 b0, b1;
    s32 val;
    s32 bpm;
    s32 prod;
    u8 *bytes;
    u32 divisor;
    SequenceState *state = g_ss_score_table[arg0] + arg1;

    switch (arg2) {
    case 0x51:
        bytes = state->field_4;
        state->field_4 = bytes + 1;
        b0 = bytes[0];
        state->field_4 = bytes + 2;
        b1 = bytes[1];
        state->field_4 = bytes + 3;
        val = (b0 << 16) | (b1 << 8) | bytes[2];
        bpm = 60000000 / val;
        prod = state->field_4A * bpm;
        fifteen_ticks = g_spawns_base << 4;
        fifteen_ticks -= g_spawns_base;
        divisor = clock_divisor(fifteen_ticks);
        state->field_8C = bpm;
        if ((u32)(prod * 10) < divisor) {
            u32 tmp = (u32)(g_spawns_base * 600) / (u32)prod;
            state->field_6E = tmp;
            state->field_70 = tmp;
            {
                s32 z = (s32)state & 1;
                if ((z >> 1) == 0) {
                    goto L_end;
                }
                if (divisor == 0) goto L_else;
                state->field_88 = 0;
                if ((s32)divisor < 0) goto L_else;
                state->field_88 = 0;
                if ((s32)divisor > 0) goto L_else;
                state->field_88 = 0;
                if ((s32)divisor <= 0) goto L_else;
                state->field_88 = 0;
            }
        } else {
            u32 tmp;
        L_else:
            tmp = (u32)(state->field_4A * state->field_8C * 10) / divisor;
            state->field_6E = -1;
            state->field_70 = tmp;
            if ((u32)(fifteen_ticks * 2) < (u32)((u32)(state->field_4A * state->field_8C * 10) % divisor)) {
                state->field_70 = tmp + 1;
            }
        }
    L_end:
        state->field_88 = _SsReadDeltaValue(arg0, arg1);
        break;
    case 0x2F:
        state->field_48++;
        if (state->field_46 == 0) {
            state->field_80 = 0;
            state->field_27 = 0;
            state->field_88 = 0;
            state->field_4 = state->field_8;
        } else if ((s16)state->field_48 < state->field_46) {
            state->field_80 = 0;
            state->field_27 = 0;
            state->field_88 = 0;
            state->field_4 = state->field_8;
            state->field_C = state->field_8;
        } else {
            (g_ss_score_table[arg0] + arg1)->field_90 &= ~1;
            (g_ss_score_table[arg0] + arg1)->field_90 &= ~8;
            (g_ss_score_table[arg0] + arg1)->field_90 &= ~2;
            (g_ss_score_table[arg0] + arg1)->field_90 |= 0x200;
            (g_ss_score_table[arg0] + arg1)->field_90 |= 4;
            state->field_2B = 0;
            state->field_C = state->field_8;
            if (state->field_3C != 0xFF) {
                state->field_2B = 0;
                _SsSndNextSep(state->field_3C, state->field_0);
                SpuVmSeqKeyOff((arg1 << 8) | arg0);
            }
            SpuVmSeqKeyOff((arg1 << 8) | arg0);
            state->field_88 = state->field_70;
        }
        break;
    }
}
