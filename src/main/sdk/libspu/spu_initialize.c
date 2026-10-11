/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* CC1_FLAGS: -O2 -fno-strength-reduce */
#include "common.h"

void func_8004DA9C(s32);              /* extern */
extern u16 D_80056228[];
extern u16 D_80056238[];
extern s32 D_8005C520;
extern s32 D_8005E548;
extern s32 D_8005FF4C;
typedef void (*SequenceCallback)();
extern SequenceCallback D_80060498[];

void func_8004970C(void) {
    u16 *defaults;
    SequenceCallback *row;
    SequenceCallback *slot;
    s32 index;
    s32 register_index;
    s32 count;
    volatile u16 *registers;
    u16 *source;
    u16 value;
    u16 global_value;

    registers = (volatile u16 *)0x1F801C00;
    index = 0;
    defaults = D_80056228;
    do {
        count = 0;
        source = defaults;
write_voice_register:
        value = *source;
        source += 1;
        count += 1;
        *registers = value;
        registers += 1;
        if (count < 8) {
            goto write_voice_register;
        }
        index += 1;
    } while (index < 0x18);
    registers = (volatile u16 *)0x1F801D80;
    register_index = 0;
    source = D_80056238;
    do {
        global_value = *source;
        source += 1;
        register_index += 1;
        *registers = global_value;
        registers += 1;
    } while (register_index < 0x10);
    func_8004DA9C(0x18);
    count = 0;
    row = D_80060498;
    do {
        index = 0xF;
        slot = row + 15;
clear_callback:
        *slot = 0;
        index -= 1;
        slot -= 1;
        if (index >= 0) {
            goto clear_callback;
        }
        count += 1;
        row += 16;
    } while (count < 0x20);
    D_8005FF4C = 0x3C;
    D_8005E548 = 0;
    D_8005C520 = 0;
}
