/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
s32 _SsReadDeltaValue(s16,s16);
void SsUtSetReverbDepth(s16,s16);
void _SsContResetAll(s16 sequence,s16 channel,u8 value) {
    SequenceState *state=g_ss_score_table[sequence]+channel;
    s16 depth=value;
    SsUtSetReverbDepth(depth,depth);
    state->field_88=_SsReadDeltaValue(sequence,channel);
}
