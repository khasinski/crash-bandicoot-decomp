/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"




void _SsClose(s16 arg0) {
    s32 i;

    SpuVmSetSeqVol(arg0, 0, 0, 1);
    SpuVmSeqKeyOff(arg0);
    g_ss_open_seq_mask &= ~(1 << arg0);
    for (i = 0; i < g_ss_sep_max; i++) {
        g_ss_score_table[arg0][i].field_90 = 0;
        g_ss_score_table[arg0][i].field_3C = 0xFF;
        g_ss_score_table[arg0][i].field_0 = 0;
        g_ss_score_table[arg0][i].field_3E = 0;
        g_ss_score_table[arg0][i].field_40 = 0;
        g_ss_score_table[arg0][i].field_94 = 0;
        g_ss_score_table[arg0][i].field_98 = 0;
        g_ss_score_table[arg0][i].field_42 = 0;
        g_ss_score_table[arg0][i].field_A4 = 0;
        g_ss_score_table[arg0][i].field_A0 = 0;
        g_ss_score_table[arg0][i].field_9C = 0;
        g_ss_score_table[arg0][i].field_44 = 0;
        g_ss_score_table[arg0][i].field_74 = 0x7F;
        g_ss_score_table[arg0][i].field_76 = 0x7F;
    }
}

void SsSeqClose(s16 arg0) {
    _SsClose(arg0);
}
