/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

typedef struct {
    u8 gap0[0x3E];
    s16 field_3E;
    s16 field_40;
    s16 field_42;
    u8 gap44[0x78 - 0x44];
    u16 field_78;
    u16 field_7A;
    u8 gap7C[0x90 - 0x7C];
    s32 field_90;
    u32 field_94;
    u32 field_98;
    u8 gap9C[0xAC - 0x9C];
} SequenceState;

extern SequenceState *D_80060418[];

void func_8004D680(void);
void func_8004C39C(s32, s32);
void func_8004BDB4(s16, s16);
void func_8004C074(s16, s16);
void func_8004CDCC(s32, s32);
void func_8004C300(s32, s32);
void func_8004C764(s32, s32);
void func_8004C7CC(s32, s32);
void func_8004FF54(s32, u16 *, u16 *);
void func_8004F998(s32, s32, s32, s32);

void func_8004BB7C(void) {
    s32 var_s0;
    s32 var_s2;

    if (D_8005C520 == 1) {
        return;
    }
    D_8005C520 = 1;
    func_8004D680();
    for (var_s2 = 0; var_s2 < D_80060C98; var_s2++) {
        if ((1 << var_s2) & D_8005E548) {
            for (var_s0 = 0; var_s0 < D_80060CA0; var_s0++) {
                if (D_80060418[var_s2][var_s0].field_90 & 1) {
                    func_8004C39C(var_s2, var_s0);
                    if (D_80060418[var_s2][var_s0].field_90 & 0x10) {
                        func_8004BDB4(var_s2, var_s0);
                    }
                    if (D_80060418[var_s2][var_s0].field_90 & 0x20) {
                        func_8004C074(var_s2, var_s0);
                    }
                    if (D_80060418[var_s2][var_s0].field_90 & 0x40) {
                        func_8004CDCC(var_s2, var_s0);
                    }
                    if (D_80060418[var_s2][var_s0].field_90 & 0x80) {
                        func_8004CDCC(var_s2, var_s0);
                    }
                }
                if (D_80060418[var_s2][var_s0].field_90 & 2) {
                    func_8004C300(var_s2, var_s0);
                }
                if (D_80060418[var_s2][var_s0].field_90 & 8) {
                    func_8004C764(var_s2, var_s0);
                }
                if (D_80060418[var_s2][var_s0].field_90 & 4) {
                    func_8004C7CC(var_s2, var_s0);
                    D_80060418[var_s2][var_s0].field_90 = 0;
                }
            }
        }
    }
    D_8005C520 = 0;
}

void func_8004BDB4(s16 arg0, s16 arg1) {
    u16 sp10;
    u16 sp12;
    SequenceState *temp_s0;

    temp_s0 = &D_80060418[arg0][arg1];
    temp_s0->field_98 -= 1;
    if (temp_s0->field_42 > 0) {
        if ((temp_s0->field_98 % temp_s0->field_42) == 0) {
            temp_s0->field_40 -= 1;
            if (temp_s0->field_40 >= 0) {
                func_8004FF54((arg1 << 8) | arg0, &sp10, &sp12);
                if ((sp10 + 1) <= (sp10 + temp_s0->field_40)) {
                    func_8004F998((arg1 << 8) | arg0, sp10 + 1, sp12 + 1, 1);
                }
            } else {
                func_8004F998((arg1 << 8) | arg0, 0x7F, 0x7F, 1);
                D_80060418[arg0][arg1].field_90 &= ~0x10;
            }
            if ((temp_s0->field_98 == 0) || (temp_s0->field_40 == 0)) {
                D_80060418[arg0][arg1].field_90 &= ~0x10;
            }
        }
    } else if (temp_s0->field_42 < 0) {
        temp_s0->field_40 += temp_s0->field_42;
        if (temp_s0->field_40 >= 0) {
            func_8004FF54((arg1 << 8) | arg0, &sp10, &sp12);
            if (((sp10 - temp_s0->field_42) >= 0x7F) && ((sp12 - temp_s0->field_42) >= 0x7F)) {
                func_8004F998((arg1 << 8) | arg0, 0x7F, 0x7F, 1);
            }
            if ((u32)((temp_s0->field_94 - temp_s0->field_98) * -temp_s0->field_42) < (u32)temp_s0->field_3E) {
                func_8004F998((arg1 << 8) | arg0, sp10 - temp_s0->field_42, sp12 - temp_s0->field_42, 1);
            }
        } else {
            func_8004F998((arg1 << 8) | arg0, 0x7F, 0x7F, 1);
            D_80060418[arg0][arg1].field_90 &= ~0x10;
        }
        if ((temp_s0->field_98 == 0) || (temp_s0->field_40 == 0)) {
            D_80060418[arg0][arg1].field_90 &= ~0x10;
        }
    }
    func_8004FF54((arg1 << 8) | arg0, &temp_s0->field_78, &temp_s0->field_7A);
}

void func_8004C074(s16 arg0, s16 arg1) {
    u16 sp10;
    u16 sp12;
    SequenceState *temp_s0;

    temp_s0 = &D_80060418[arg0][arg1];
    temp_s0->field_98 -= 1;
    if (temp_s0->field_42 > 0) {
        if ((temp_s0->field_98 % temp_s0->field_42) == 0) {
            temp_s0->field_40 -= 1;
            if (temp_s0->field_40 > 0) {
                func_8004FF54((arg1 << 8) | arg0, &sp10, &sp12);
                if (((sp10 - temp_s0->field_40) <= 0) || ((sp12 - temp_s0->field_40) <= 0) || (sp10 == 1)) {
                    func_8004F998((arg1 << 8) | arg0, 1, 1, 1);
                } else {
                    func_8004F998((arg1 << 8) | arg0, sp10 - 1, sp12 - 1, 1);
                }
            } else {
                D_80060418[arg0][arg1].field_90 &= ~0x20;
            }
            if ((temp_s0->field_98 == 0) || (temp_s0->field_40 == 0)) {
                D_80060418[arg0][arg1].field_90 &= ~0x20;
            }
        }
    } else {
        temp_s0->field_40 += temp_s0->field_42;
        if (temp_s0->field_40 > 0) {
            func_8004FF54((arg1 << 8) | arg0, &sp10, &sp12);
            if (((u32)temp_s0->field_3E >= (u32)((temp_s0->field_94 - temp_s0->field_98) * -temp_s0->field_42)) && (-temp_s0->field_42 < sp10)) {
                func_8004F998((arg1 << 8) | arg0, sp10 + temp_s0->field_42, sp12 + temp_s0->field_42, 1);
            } else {
                func_8004F998((arg1 << 8) | arg0, 1, 1, 1);
            }
        } else {
            D_80060418[arg0][arg1].field_90 &= ~0x20;
        }
        if ((temp_s0->field_98 == 0) || (temp_s0->field_40 == 0)) {
            D_80060418[arg0][arg1].field_90 &= ~0x20;
        }
    }
    func_8004FF54((arg1 << 8) | arg0, &temp_s0->field_78, &temp_s0->field_7A);
}

