/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
void _SsContNrpn2(sequence,channel,value)
s16 sequence,channel;
u8 value;
{
    SequenceState *state=g_ss_score_table[sequence]+channel;
    switch(value) {
    case 20:
        state->field_16=value;
        state->field_27=1;
        state->field_88=_SsReadDeltaValue(sequence,channel);
        state->field_C=state->field_4;
        break;
    case 30:
        state->field_16=value;
        if(state->field_28==0) {
            state->field_10=0;
            state->field_88=_SsReadDeltaValue(sequence,channel);
        } else if(state->field_28<127) {
            state->field_28--;
            state->field_88=_SsReadDeltaValue(sequence,channel);
            if(state->field_28!=0) {
                state->field_4=state->field_C;
            } else state->field_10=0;
        } else {
            _SsReadDeltaValue(sequence,channel);
            state->field_88=0;
            state->field_4=state->field_C;
        }
        break;
    default:
        state->field_16=value;
        state->field_2A++;
        state->field_88=_SsReadDeltaValue(sequence,channel);
        break;
    }
}
