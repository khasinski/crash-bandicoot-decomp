/* GCC_VERSION: 2.5.7 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
/* GCC_CPU: r4000 */
void _SsSndNextSep(s16 sequence, s16 channel) {
    SequenceState *state;
    state = &g_ss_score_table[sequence][channel];
    state->field_46 = 1;
    state->field_48 = 0;
    g_ss_score_table[sequence][channel].field_90 &= ~0x100;
    g_ss_score_table[sequence][channel].field_90 &= ~8;
    g_ss_score_table[sequence][channel].field_90 &= ~2;
    g_ss_score_table[sequence][channel].field_90 &= ~4;
    g_ss_score_table[sequence][channel].field_90 &= ~0x200;
    state->field_2B = 1;
    state->field_4 = state->field_8;
    g_ss_score_table[sequence][channel].field_90 |= 1;
}
