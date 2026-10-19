/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
s32 _SsReadDeltaValue(s16,s16);
s32 SpuVmPitchBend();
void _SsSetPitchBend(s16 sequence,s16 channel) {
    SequenceState *state=g_ss_score_table[sequence]+channel;
    u8 *bytes=(u8 *)state;
    u8 *cursor=state->field_4;
    u8 value;
    state->field_4=cursor+1;
    value=*cursor;
    SpuVmPitchBend((channel<<8)|sequence,state->field_4C,bytes[0x2C+bytes[0x12]],value);
    state->field_88=_SsReadDeltaValue(sequence,channel);
}
