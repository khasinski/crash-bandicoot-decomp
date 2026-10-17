/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

extern s32 D_8005C520;
extern s16 D_80060C98;
extern s16 D_80060CA0;
extern s32 D_8005E548;
extern u8 *D_80060418[];

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
                if (*(s32 *)(D_80060418[var_s2] + (var_s0 * 0xAC) + 0x90) & 1) {
                    func_8004C39C(var_s2, var_s0);
                    if (*(s32 *)(D_80060418[var_s2] + (var_s0 * 0xAC) + 0x90) & 0x10) {
                        func_8004BDB4(var_s2, var_s0);
                    }
                    if (*(s32 *)(D_80060418[var_s2] + (var_s0 * 0xAC) + 0x90) & 0x20) {
                        func_8004C074(var_s2, var_s0);
                    }
                    if (*(s32 *)(D_80060418[var_s2] + (var_s0 * 0xAC) + 0x90) & 0x40) {
                        func_8004CDCC(var_s2, var_s0);
                    }
                    if (*(s32 *)(D_80060418[var_s2] + (var_s0 * 0xAC) + 0x90) & 0x80) {
                        func_8004CDCC(var_s2, var_s0);
                    }
                }
                if (*(s32 *)(D_80060418[var_s2] + (var_s0 * 0xAC) + 0x90) & 2) {
                    func_8004C300(var_s2, var_s0);
                }
                if (*(s32 *)(D_80060418[var_s2] + (var_s0 * 0xAC) + 0x90) & 8) {
                    func_8004C764(var_s2, var_s0);
                }
                if (*(s32 *)(D_80060418[var_s2] + (var_s0 * 0xAC) + 0x90) & 4) {
                    func_8004C7CC(var_s2, var_s0);
                    *(s32 *)(D_80060418[var_s2] + (var_s0 * 0xAC) + 0x90) = 0;
                }
            }
        }
    }
    D_8005C520 = 0;
}

void func_8004BDB4(s16 arg0, s16 arg1) {
    u16 sp10;
    u16 sp12;
    u8 *temp_s0;

    temp_s0 = (arg1 * 0xAC) + D_80060418[arg0];
    *(u32 *)(temp_s0 + 0x98) -= 1;
    if (*(s16 *)(temp_s0 + 0x42) > 0) {
        if ((*(u32 *)(temp_s0 + 0x98) % *(s16 *)(temp_s0 + 0x42)) == 0) {
            *(s16 *)(temp_s0 + 0x40) -= 1;
            if (*(s16 *)(temp_s0 + 0x40) >= 0) {
                func_8004FF54((arg1 << 8) | arg0, &sp10, &sp12);
                if ((sp10 + 1) <= (sp10 + *(s16 *)(temp_s0 + 0x40))) {
                    func_8004F998((arg1 << 8) | arg0, sp10 + 1, sp12 + 1, 1);
                }
            } else {
                func_8004F998((arg1 << 8) | arg0, 0x7F, 0x7F, 1);
                *(u32 *)((arg1 * 0xAC) + D_80060418[arg0] + 0x90) &= ~0x10;
            }
            if ((*(u32 *)(temp_s0 + 0x98) == 0) || (*(s16 *)(temp_s0 + 0x40) == 0)) {
                *(u32 *)((arg1 * 0xAC) + D_80060418[arg0] + 0x90) &= ~0x10;
            }
        }
    } else if (*(s16 *)(temp_s0 + 0x42) < 0) {
        *(s16 *)(temp_s0 + 0x40) += *(s16 *)(temp_s0 + 0x42);
        if (*(s16 *)(temp_s0 + 0x40) >= 0) {
            func_8004FF54((arg1 << 8) | arg0, &sp10, &sp12);
            if (((sp10 - *(s16 *)(temp_s0 + 0x42)) >= 0x7F) && ((sp12 - *(s16 *)(temp_s0 + 0x42)) >= 0x7F)) {
                func_8004F998((arg1 << 8) | arg0, 0x7F, 0x7F, 1);
            }
            if ((u32)((*(u32 *)(temp_s0 + 0x94) - *(u32 *)(temp_s0 + 0x98)) * -*(s16 *)(temp_s0 + 0x42)) < (u32)*(s16 *)(temp_s0 + 0x3E)) {
                func_8004F998((arg1 << 8) | arg0, sp10 - *(s16 *)(temp_s0 + 0x42), sp12 - *(s16 *)(temp_s0 + 0x42), 1);
            }
        } else {
            func_8004F998((arg1 << 8) | arg0, 0x7F, 0x7F, 1);
            *(u32 *)((arg1 * 0xAC) + D_80060418[arg0] + 0x90) &= ~0x10;
        }
        if ((*(u32 *)(temp_s0 + 0x98) == 0) || (*(s16 *)(temp_s0 + 0x40) == 0)) {
            *(u32 *)((arg1 * 0xAC) + D_80060418[arg0] + 0x90) &= ~0x10;
        }
    }
    func_8004FF54((arg1 << 8) | arg0, (u16 *)(temp_s0 + 0x78), (u16 *)(temp_s0 + 0x7A));
}

void func_8004C074(s16 arg0, s16 arg1) {
    u16 sp10;
    u16 sp12;
    u8 *temp_s0;

    temp_s0 = (arg1 * 0xAC) + D_80060418[arg0];
    *(u32 *)(temp_s0 + 0x98) -= 1;
    if (*(s16 *)(temp_s0 + 0x42) > 0) {
        if ((*(u32 *)(temp_s0 + 0x98) % *(s16 *)(temp_s0 + 0x42)) == 0) {
            *(s16 *)(temp_s0 + 0x40) -= 1;
            if (*(s16 *)(temp_s0 + 0x40) > 0) {
                func_8004FF54((arg1 << 8) | arg0, &sp10, &sp12);
                if (((sp10 - *(s16 *)(temp_s0 + 0x40)) <= 0) || ((sp12 - *(s16 *)(temp_s0 + 0x40)) <= 0) || (sp10 == 1)) {
                    func_8004F998((arg1 << 8) | arg0, 1, 1, 1);
                } else {
                    func_8004F998((arg1 << 8) | arg0, sp10 - 1, sp12 - 1, 1);
                }
            } else {
                *(u32 *)((arg1 * 0xAC) + D_80060418[arg0] + 0x90) &= ~0x20;
            }
            if ((*(u32 *)(temp_s0 + 0x98) == 0) || (*(s16 *)(temp_s0 + 0x40) == 0)) {
                *(u32 *)((arg1 * 0xAC) + D_80060418[arg0] + 0x90) &= ~0x20;
            }
        }
    } else {
        *(s16 *)(temp_s0 + 0x40) += *(s16 *)(temp_s0 + 0x42);
        if (*(s16 *)(temp_s0 + 0x40) > 0) {
            func_8004FF54((arg1 << 8) | arg0, &sp10, &sp12);
            if (((u32)*(s16 *)(temp_s0 + 0x3E) >= (u32)((*(u32 *)(temp_s0 + 0x94) - *(u32 *)(temp_s0 + 0x98)) * -*(s16 *)(temp_s0 + 0x42))) && (-*(s16 *)(temp_s0 + 0x42) < sp10)) {
                func_8004F998((arg1 << 8) | arg0, sp10 + *(s16 *)(temp_s0 + 0x42), sp12 + *(s16 *)(temp_s0 + 0x42), 1);
            } else {
                func_8004F998((arg1 << 8) | arg0, 1, 1, 1);
            }
        } else {
            *(u32 *)((arg1 * 0xAC) + D_80060418[arg0] + 0x90) &= ~0x20;
        }
        if ((*(u32 *)(temp_s0 + 0x98) == 0) || (*(s16 *)(temp_s0 + 0x40) == 0)) {
            *(u32 *)((arg1 * 0xAC) + D_80060418[arg0] + 0x90) &= ~0x20;
        }
    }
    func_8004FF54((arg1 << 8) | arg0, (u16 *)(temp_s0 + 0x78), (u16 *)(temp_s0 + 0x7A));
}

