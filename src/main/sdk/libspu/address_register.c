#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Align a byte address, convert to SPU units, optionally write a register. */
extern s32 D_80055904,D_80055908;
extern u32 D_8005590C,D_80055910;
extern u16 *D_800558E4;
extern s32 D_80055950;
extern s32 D_80055954;
extern s32 D_80055958;
s32 func_80047190(s32);

u32 func_80046E00(s32 reg,u32 address) {
    u32 units;
    if (D_80055904 && address % D_8005590C) {
        address += D_8005590C;
        address &= ~D_80055910;
    }
    units = address >> D_80055908;
    switch (reg) {
    case -1: return units & 0xffff;
    case -2: return address;
    default: D_800558E4[reg] = units; return address;
    }
}

u32 func_80046EA4(s32 reg, s32 mode) {
    u16 units = D_800558E4[reg];
    switch (mode) {
    case -1:
        return units;
    default:
        return units << D_80055908;
    }
}

s32 func_80046EE0(s32 mode) {
    u16 ctrl;
    switch (mode) {
    case 0:
        D_80055950 = 0;
        ctrl = D_800558E4[0xD5];
        ctrl &= ~0x80;
        D_800558E4[0xD5] = ctrl;
        break;
    case 1:
        if (D_80055954 != 1 && func_80047190(D_80055958)) {
            D_80055950 = 0;
            ctrl = D_800558E4[0xD5];
            ctrl &= ~0x80;
            D_800558E4[0xD5] = ctrl;
        } else {
            D_80055950 = mode;
            ctrl = D_800558E4[0xD5];
            ctrl |= 0x80;
            D_800558E4[0xD5] = ctrl;
        }
        break;
    }
    return D_80055950;
}
