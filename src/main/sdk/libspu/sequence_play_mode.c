/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
s16 SpuVmSetSeqVol();
void Snd_SetPlayMode(s16 sequence,s16 channel,u8 mode,s16 repeat) {
    SequenceState *state = &g_ss_score_table[sequence][channel];
    state->field_90 &= ~0x200;
    g_ss_score_table[sequence][channel].field_90 &= ~4;
    state->field_46 = repeat;
    if (mode==1) {
        g_ss_score_table[sequence][channel].field_90 |= 1;
        state->field_48 = 0;
        state->field_2B = 1;
        SpuVmSetSeqVol((channel<<8)|sequence, state->field_74, state->field_76, 0);
    } else if (mode==0) {
        g_ss_score_table[sequence][channel].field_90 |= 2;
    }
}
