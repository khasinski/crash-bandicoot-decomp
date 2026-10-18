#include "common.h"

/* GCC_VERSION: 2.6.3 */
void func_80043354(u32, u32);
extern volatile u16 *D_800558E4;
/* Retail tests and then reloads this shared completion callback slot. */
extern void (*volatile D_80055918)(void);

void func_800466A0(void) {
    /* Retail stores and reloads both delay words on the stack. */
    volatile s32 delay_count;
    volatile u32 delay_value;
    s32 poll_count;
    volatile u16 *registers;

    if (D_80055930 == 0) {
        delay_value = 13;
        for (delay_count = 0; delay_count < 240; delay_count++) {
            delay_value *= 3;
        }
        delay_value = 13;
        for (delay_count = 0; delay_count < 240; delay_count++) {
            delay_value *= 3;
        }
        delay_value = 13;
        for (delay_count = 0; delay_count < 240; delay_count++) {
            delay_value *= 3;
        }
    }
    registers = D_800558E4;
    registers[0xD5] &= 0xFFCF;
    poll_count = 0;
    while ((registers[0xD5] & 0x30) && ++poll_count < 0xF01) {
    }
    if (D_80055918 != NULL) {
        D_80055918();
    } else {
        func_80043354(0xF0000009, 0x20);
    }
}
