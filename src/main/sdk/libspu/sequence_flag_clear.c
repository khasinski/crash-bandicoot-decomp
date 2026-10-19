/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
/* The packed selector is passed as a word by this SDK caller. */
void SpuVmSeqKeyOff();
void _SsSndPause(s16 sequence,s16 channel)
{
    SequenceState *state = &g_ss_score_table[sequence][channel];
    SpuVmSeqKeyOff((channel<<8)|sequence);
    state->field_2B = 0;
    g_ss_score_table[sequence][channel].field_90 &= ~2;
}
