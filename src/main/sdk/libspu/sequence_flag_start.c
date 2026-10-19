/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
void _SsSndSetReplayMode(s16 sequence,s16 channel) {
    SequenceState *state = &g_ss_score_table[sequence][channel];
    u32 word = state->field_90;
    if (!(word&0x204)) {
        if (!(word&0x100)) {
            state->field_90 = word&~2;
            g_ss_score_table[sequence][channel].field_90 |= 8;
            g_ss_score_table[sequence][channel].field_90 |= 1;
        }
    }
}
