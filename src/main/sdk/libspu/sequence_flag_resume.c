/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
void _SsSndReplay(s16 sequence,s16 channel) {
    SequenceState *state = &g_ss_score_table[sequence][channel];
    state->field_2B = 1;
    g_ss_score_table[sequence][channel].field_90 &= ~8;
}
