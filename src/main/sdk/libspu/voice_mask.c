#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Read, set or clear a 24-bit mask across two SPU registers. */

extern volatile u16 *D_800558E4;

s32 func_80047C84(s32 mode, u32 mask, s32 low_index, s32 high_index) {
    s32 value;
    volatile u16 *low_register;
    volatile u16 *high_register;
    u16 high_value;

    high_register = D_800558E4 + high_index;
    low_register = D_800558E4 + low_index;
    value = ((*high_register & 0xFF) << 0x10) | *low_register;
    if (mode != 0) {
        if (mode == 1) {
            value |= mask & 0xFFFFFF;
            *low_register |= mask;
            high_value = *high_register | ((mask >> 0x10) & 0xFF);
            goto write_high;
        }
    } else {
        value &= ~(mask & 0xFFFFFF);
        *low_register &= ~mask;
        high_value = *high_register & ~((mask >> 0x10) & 0xFF);
write_high:
        *high_register = high_value;
    }
    return value & 0xFFFFFF;
}
