#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Align a byte address, convert to SPU units, optionally write a register. */


s32 _SpuIsInAllocateArea_(s32);

u32 _spu_FsetRXXa(s32 reg,u32 address) {
    u32 units;
    if (D_80055904 && address % D_8005590C) {
        address += D_8005590C;
        address &= ~D_80055910;
    }
    units = address >> g_spu_trans_mode;
    switch (reg) {
    case -1: return units & 0xffff;
    case -2: return address;
    default: g_spu_RXX[reg] = units; return address;
    }
}

u32 _spu_FgetRXXa(s32 reg, s32 mode) {
    u16 units = g_spu_RXX[reg];
    switch (mode) {
    case -1:
        return units;
    default:
        return units << g_spu_trans_mode;
    }
}

s32 SpuSetReverb(s32 mode) {
    u16 ctrl;
    switch (mode) {
    case 0:
        D_80055950 = 0;
        ctrl = g_spu_RXX[0xD5];
        ctrl &= ~0x80;
        g_spu_RXX[0xD5] = ctrl;
        break;
    case 1:
        if (D_80055954 != 1 && _SpuIsInAllocateArea_(D_80055958)) {
            D_80055950 = 0;
            ctrl = g_spu_RXX[0xD5];
            ctrl &= ~0x80;
            g_spu_RXX[0xD5] = ctrl;
        } else {
            D_80055950 = mode;
            ctrl = g_spu_RXX[0xD5];
            ctrl |= 0x80;
            g_spu_RXX[0xD5] = ctrl;
        }
        break;
    }
    return D_80055950;
}
