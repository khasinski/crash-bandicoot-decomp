/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
void _SsNoteOff(s16 sequence,s16 channel,u8 value) {
    SequenceState *state=g_ss_score_table[sequence]+channel;
    state->field_2C[state->field_12]=value;
    state->field_88=_SsReadDeltaValue(sequence,channel);
}
