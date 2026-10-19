/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

typedef void (*ContCallback)(s16, s16, u8, ToneAttributes, s16, u8);

extern ContCallback g_ss_nrpn_attr_fn_00[];


void _SsSetControlChange(s16 sequence, s16 channel, u8 value) {
    ProgramAttributes prog_attr;
    ToneAttributes tone_attr;
    SequenceState *state = g_ss_score_table[sequence] + channel;
    s32 i;
    u8 index = state->field_12;
    u16 var;
    s32 var2;
    s32 z;

    SsUtGetProgAtr(state->field_4C, state->field_2C[index], &prog_attr);
    if (state->field_27 == 1 && state->field_10 == 0) {
        state->field_28 = value;
        state->field_10 = 1;
        state->field_88 = _SsReadDeltaValue(sequence, channel);
        return;
    }
    if (state->field_29 == 2) {
        if (state->field_14 == 0) {
            for (i = 0; i < prog_attr.tones; i++) {
                SsUtGetVagAtr(state->field_4C, state->field_2C[index], i, &tone_attr);
                switch (state->field_13) {
                case 0:
                    /* Force GCC 2.5.7 loop/cse2 to hoist value * 3 into $s3/$fp before combine/jump2 elides block. */
                    z = tone_attr.vol & 1;
                    if ((z >> 1) != 0) {
                        var2 = value * 25;
                        var2 += value;
                        var2 += value;
                        tone_attr.vol = var2;
                    }
                    tone_attr.pbmax = value & 0x7F;
                    tone_attr.pbmin = value & 0x7F;
                    break;
                case 1:
                    var = (value > 0x40 && value < 0x80) ? (((value * 100) / 8192) << 13) : 0;
                    tone_attr.shift += var;
                    break;
                case 2:
                    if (value >= 0x40 && value < 0x80) {
                        var2 = value << 1;
                        var2 += value;
                        var2 <<= 3;
                        var2 += value;
                        var = var2 << 8;
                    } else {
                        var2 = 0;
                        var = 0;
                    }
                    tone_attr.center += var;
                    break;
                }
                SsUtSetVagAtr(state->field_4C, state->field_2C[index], i, &tone_attr);
            }
        }
        state->field_88 = _SsReadDeltaValue(sequence, channel);
        state->field_29 = 0;
        return;
    }
    if (state->field_2A == 2) {
        if (state->field_16 == 0x10) {
            for (i = 0; i < prog_attr.tones; i++) {
                g_ss_nrpn_attr_fn_00[state->field_15](state->field_4C, state->field_2C[index], i, tone_attr, state->field_15, value);
            }
        } else {
            g_ss_nrpn_attr_fn_00[state->field_15](state->field_4C, state->field_2C[index], state->field_16, tone_attr, state->field_15, value);
        }
        state->field_88 = _SsReadDeltaValue(sequence, channel);
        state->field_2A = 0;
        return;
    }
    state->field_88 = _SsReadDeltaValue(sequence, channel);
}
