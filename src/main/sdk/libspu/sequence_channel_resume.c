/* GCC_VERSION: 2.5.7 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
/* GCC_CPU: r4000 */
s16 SpuVmGetSeqVol(s16, u16 *, u16 *);
void _SsSndSetPauseMode(s16 sequence, s16 channel) {
    SequenceState *state = &g_ss_score_table[sequence][channel];
    SpuVmGetSeqVol((channel << 8) | sequence, &state->field_78, &state->field_7A);
    g_ss_score_table[sequence][channel].field_90 &= ~1;
    g_ss_score_table[sequence][channel].field_90 &= ~8;
    g_ss_score_table[sequence][channel].field_90 |= 2;
}
