/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
/* This SDK call passes promoted words, including the packed selector. */
void _SsContModulation(s16 sequence,s16 channel,u8 velocity) {
    SequenceState *state=g_ss_score_table[sequence]+channel;
    s32 index=state->field_12;
    SpuVmSetVol((channel<<8)|sequence,state->field_4C,state->field_2C[index],velocity,state->field_17[index]);
    state->gains[index]=velocity;
    state->field_88=_SsReadDeltaValue(sequence,channel);
}
