/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
void _SsContRpn1(s16 sequence,s16 channel,u8 value) {
    SequenceState *state=g_ss_score_table[sequence]+channel;
    state->field_13=value;
    state->field_29++;
    state->field_88=_SsReadDeltaValue(sequence,channel);
}
void _SsContRpn2(s16 sequence,s16 channel,u8 value) {
    SequenceState *state=g_ss_score_table[sequence]+channel;
    state->field_14=value;
    state->field_29++;
    state->field_88=_SsReadDeltaValue(sequence,channel);
}
