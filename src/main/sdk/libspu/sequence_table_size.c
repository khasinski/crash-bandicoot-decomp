/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"



void SsSetTableSize(void *table, s16 s_max, s16 t_max) {
    s32 i;
    s32 j;

    D_80060C98 = s_max;
    D_80060CA0 = t_max;
    for (i = 0; i < s_max; i++) {
        g_ss_score_table[i] = (SequenceState *)table + i * t_max;
    }
    for (i = 0; i < D_80060C98; i++) {
        for (j = 0; j < D_80060CA0; j++) {
            g_ss_score_table[i][j].field_90 = 0;
            g_ss_score_table[i][j].field_3C = 0xFF;
            g_ss_score_table[i][j].field_0 = 0;
            g_ss_score_table[i][j].field_3E = 0;
            g_ss_score_table[i][j].field_40 = 0;
            g_ss_score_table[i][j].field_94 = 0;
            g_ss_score_table[i][j].field_98 = 0;
            g_ss_score_table[i][j].field_42 = 0;
            g_ss_score_table[i][j].field_A4 = 0;
            g_ss_score_table[i][j].field_A0 = 0;
            g_ss_score_table[i][j].field_9C = 0;
            g_ss_score_table[i][j].field_44 = 0;
            g_ss_score_table[i][j].field_74 = 0x7F;
            g_ss_score_table[i][j].field_76 = 0x7F;
            g_ss_score_table[i][j].field_78 = 0x7F;
            g_ss_score_table[i][j].field_7A = 0x7F;
        }
    }
}
