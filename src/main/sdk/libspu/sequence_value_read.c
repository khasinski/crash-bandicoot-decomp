/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
void _SsSetProgramChange(s16 sequence,s16 channel)
{
    SequenceState *state=g_ss_score_table[sequence]+channel;
    u8 *cursor=state->field_4;
    state->field_4=cursor+1;
    state->field_4C=*cursor;
    state->field_88=_SsReadDeltaValue(sequence,channel);
}
