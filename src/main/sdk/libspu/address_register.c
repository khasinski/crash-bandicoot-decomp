#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Align a byte address, convert to SPU units, optionally write a register. */
extern s32 D_80055904,D_80055908;
extern u32 D_8005590C,D_80055910;
extern volatile u16 *D_800558E4;
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
