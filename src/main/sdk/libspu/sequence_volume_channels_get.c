/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
s32 SpuVmGetSeqLVol(s32 selector) {
    s32 channel=(selector&0xFF00)>>8;
    SequenceState *state=&g_ss_score_table[selector&0xFF][channel];
    D_8005E56E=selector;
    return *(s16 *)&state->field_74;
}
s32 SpuVmGetSeqRVol(s32 selector) {
    s32 channel=(selector&0xFF00)>>8;
    SequenceState *state=&g_ss_score_table[selector&0xFF][channel];
    D_8005E56E=selector;
    return *(s16 *)&state->field_76;
}
