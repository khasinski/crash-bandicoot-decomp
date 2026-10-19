/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
void _SsContDataEntry(s16 sequence,s16 channel) {
    SequenceState *state=g_ss_score_table[sequence]+channel;
    SsUtReverbOff();
    SpuVmDamperOff();
    state->field_2C[state->field_12]=state->field_12;
    state->field_13=0;
    state->field_14=0;
    state->gains[state->field_12]=127;
    state->field_17[state->field_12]=64;
    state->field_88=_SsReadDeltaValue(sequence,channel);
}
