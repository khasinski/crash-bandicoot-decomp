/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
/* This SDK call passes promoted words, including the packed selector. */
s32 SpuVmSetVol();
s32 _SsReadDeltaValue(s16,s16);
void _SsContPortaTime(s16 sequence,s16 channel,u8 value) {
    SequenceState *state=g_ss_score_table[sequence]+channel;
    s32 index=state->field_12;
    u8 *slot=&state->field_0+index;
    SpuVmSetVol((channel<<8)|sequence,state->field_4C,slot[0x2C],state->gains[index],value);
    slot[0x17]=value;
    state->field_88=_SsReadDeltaValue(sequence,channel);
}
