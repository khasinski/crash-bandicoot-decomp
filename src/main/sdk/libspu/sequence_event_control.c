/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
typedef void (*SequenceCallback)(s16,s16,u8);
extern SequenceCallback g_ss_mark_callbacks[][16];
s32 _SsReadDeltaValue(s16,s16);
void _SsContNrpn1(sequence,channel,value)
s16 sequence,channel;
u8 value;
{
    SequenceState *state=g_ss_score_table[(s16)sequence]+(s16)channel;
    SequenceCallback callback;
    if (state->field_27==1 && state->field_10==0) {
        state->field_28=value;
        state->field_10=1;
    } else {
        if(state->field_16==30) goto check_callback;
        if(state->field_16==20) goto check_callback;
        state->field_15=value;
        state->field_2A++;
    }
check_callback:
    if (state->field_16==40) {
        callback=g_ss_mark_callbacks[(s16)sequence][(s16)channel];
        if(callback) callback(sequence,channel,value);
    }
    state->field_88=_SsReadDeltaValue(sequence,channel);
}
