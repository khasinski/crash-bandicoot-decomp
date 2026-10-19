/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"



void SpuVmFlush(void);
void _SsSndPlay(s32, s32);
void _SsSndCrescendo(s16, s16);
void _SsSndDecrescendo(s16, s16);
void _SsSndSetRit(s32, s32);
void _SsSndPause(s32, s32);
void _SsSndReplay(s32, s32);
void _SsSndStop(s32, s32);
void SpuVmGetSeqVol(s32, u16 *, u16 *);
void SpuVmSetSeqVol(s32, s32, s32, s32);

void SsSeqCalledTbyT(void) {
    s32 var_s0;
    s32 var_s2;

    if (D_8005C520 == 1) {
        return;
    }
    D_8005C520 = 1;
    SpuVmFlush();
    for (var_s2 = 0; var_s2 < D_80060C98; var_s2++) {
        if ((1 << var_s2) & D_8005E548) {
            for (var_s0 = 0; var_s0 < D_80060CA0; var_s0++) {
                if (g_ss_score_table[var_s2][var_s0].field_90 & 1) {
                    _SsSndPlay(var_s2, var_s0);
                    if (g_ss_score_table[var_s2][var_s0].field_90 & 0x10) {
                        _SsSndCrescendo(var_s2, var_s0);
                    }
                    if (g_ss_score_table[var_s2][var_s0].field_90 & 0x20) {
                        _SsSndDecrescendo(var_s2, var_s0);
                    }
                    if (g_ss_score_table[var_s2][var_s0].field_90 & 0x40) {
                        _SsSndSetRit(var_s2, var_s0);
                    }
                    if (g_ss_score_table[var_s2][var_s0].field_90 & 0x80) {
                        _SsSndSetRit(var_s2, var_s0);
                    }
                }
                if (g_ss_score_table[var_s2][var_s0].field_90 & 2) {
                    _SsSndPause(var_s2, var_s0);
                }
                if (g_ss_score_table[var_s2][var_s0].field_90 & 8) {
                    _SsSndReplay(var_s2, var_s0);
                }
                if (g_ss_score_table[var_s2][var_s0].field_90 & 4) {
                    _SsSndStop(var_s2, var_s0);
                    g_ss_score_table[var_s2][var_s0].field_90 = 0;
                }
            }
        }
    }
    D_8005C520 = 0;
}

void _SsSndCrescendo(s16 arg0, s16 arg1) {
    u16 sp10;
    u16 sp12;
    SequenceState *temp_s0;

    temp_s0 = &g_ss_score_table[arg0][arg1];
    temp_s0->field_98 -= 1;
    if (temp_s0->field_42 > 0) {
        if ((temp_s0->field_98 % temp_s0->field_42) == 0) {
            temp_s0->field_40 -= 1;
            if (temp_s0->field_40 >= 0) {
                SpuVmGetSeqVol((arg1 << 8) | arg0, &sp10, &sp12);
                if ((sp10 + 1) <= (sp10 + temp_s0->field_40)) {
                    SpuVmSetSeqVol((arg1 << 8) | arg0, sp10 + 1, sp12 + 1, 1);
                }
            } else {
                SpuVmSetSeqVol((arg1 << 8) | arg0, 0x7F, 0x7F, 1);
                g_ss_score_table[arg0][arg1].field_90 &= ~0x10;
            }
            if ((temp_s0->field_98 == 0) || (temp_s0->field_40 == 0)) {
                g_ss_score_table[arg0][arg1].field_90 &= ~0x10;
            }
        }
    } else if (temp_s0->field_42 < 0) {
        temp_s0->field_40 += temp_s0->field_42;
        if (temp_s0->field_40 >= 0) {
            SpuVmGetSeqVol((arg1 << 8) | arg0, &sp10, &sp12);
            if (((sp10 - temp_s0->field_42) >= 0x7F) && ((sp12 - temp_s0->field_42) >= 0x7F)) {
                SpuVmSetSeqVol((arg1 << 8) | arg0, 0x7F, 0x7F, 1);
            }
            if ((u32)((temp_s0->field_94 - temp_s0->field_98) * -temp_s0->field_42) < (u32)temp_s0->field_3E) {
                SpuVmSetSeqVol((arg1 << 8) | arg0, sp10 - temp_s0->field_42, sp12 - temp_s0->field_42, 1);
            }
        } else {
            SpuVmSetSeqVol((arg1 << 8) | arg0, 0x7F, 0x7F, 1);
            g_ss_score_table[arg0][arg1].field_90 &= ~0x10;
        }
        if ((temp_s0->field_98 == 0) || (temp_s0->field_40 == 0)) {
            g_ss_score_table[arg0][arg1].field_90 &= ~0x10;
        }
    }
    SpuVmGetSeqVol((arg1 << 8) | arg0, &temp_s0->field_78, &temp_s0->field_7A);
}

void _SsSndDecrescendo(s16 arg0, s16 arg1) {
    u16 sp10;
    u16 sp12;
    SequenceState *temp_s0;

    temp_s0 = &g_ss_score_table[arg0][arg1];
    temp_s0->field_98 -= 1;
    if (temp_s0->field_42 > 0) {
        if ((temp_s0->field_98 % temp_s0->field_42) == 0) {
            temp_s0->field_40 -= 1;
            if (temp_s0->field_40 > 0) {
                SpuVmGetSeqVol((arg1 << 8) | arg0, &sp10, &sp12);
                if (((sp10 - temp_s0->field_40) <= 0) || ((sp12 - temp_s0->field_40) <= 0) || (sp10 == 1)) {
                    SpuVmSetSeqVol((arg1 << 8) | arg0, 1, 1, 1);
                } else {
                    SpuVmSetSeqVol((arg1 << 8) | arg0, sp10 - 1, sp12 - 1, 1);
                }
            } else {
                g_ss_score_table[arg0][arg1].field_90 &= ~0x20;
            }
            if ((temp_s0->field_98 == 0) || (temp_s0->field_40 == 0)) {
                g_ss_score_table[arg0][arg1].field_90 &= ~0x20;
            }
        }
    } else {
        temp_s0->field_40 += temp_s0->field_42;
        if (temp_s0->field_40 > 0) {
            SpuVmGetSeqVol((arg1 << 8) | arg0, &sp10, &sp12);
            if (((u32)temp_s0->field_3E >= (u32)((temp_s0->field_94 - temp_s0->field_98) * -temp_s0->field_42)) && (-temp_s0->field_42 < sp10)) {
                SpuVmSetSeqVol((arg1 << 8) | arg0, sp10 + temp_s0->field_42, sp12 + temp_s0->field_42, 1);
            } else {
                SpuVmSetSeqVol((arg1 << 8) | arg0, 1, 1, 1);
            }
        } else {
            g_ss_score_table[arg0][arg1].field_90 &= ~0x20;
        }
        if ((temp_s0->field_98 == 0) || (temp_s0->field_40 == 0)) {
            g_ss_score_table[arg0][arg1].field_90 &= ~0x20;
        }
    }
    SpuVmGetSeqVol((arg1 << 8) | arg0, &temp_s0->field_78, &temp_s0->field_7A);
}

