/* GCC_VERSION: 2.5.7 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
/* GCC_CPU: r4000 */
void _SsSndSetPauseMode(s16 sequence, s16 channel) {
    SequenceState *state = &g_ss_score_table[sequence][channel];
    SpuVmGetSeqVol((channel << 8) | sequence, &state->start_voll, &state->start_volr);
    g_ss_score_table[sequence][channel].flags &= ~1;
    g_ss_score_table[sequence][channel].flags &= ~8;
    g_ss_score_table[sequence][channel].flags |= 2;
}
