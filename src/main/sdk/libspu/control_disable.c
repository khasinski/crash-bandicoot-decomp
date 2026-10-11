#include "common.h"

/* GCC_VERSION: 2.6.3 */
extern volatile u16 *D_800558E4;

s32 func_80045DC4(void) {
    /* Retail stores and reloads both delay words on the stack. */
    volatile s32 delay_count;
    volatile u32 delay_value;
    u16 temp_a0;

    temp_a0 = D_800558E4[0xD5];
    D_800558E4[0xD5] = (u16) (temp_a0 & 0x7FCF);
    delay_value = 13;
    for (delay_count = 0; delay_count < 240; delay_count++) {
        delay_value *= 3;
    }
    temp_a0 &= 0xFFCF;
    D_800558E4[0xD5] = temp_a0;
    return 0;
}
