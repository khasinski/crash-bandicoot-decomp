/* GCC_VERSION: 2.5.7 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
/* GCC_CPU: r4000 */
s32 func_80050728(s16, s16);
extern u8 D_8005E578[];
extern u8 *D_8005CFCC;
typedef struct {
    u8 tones, volume, priority, mode, pan, unused;
    u16 attributes;
    u8 tail[8];
} ProgramAttributes;
s32 func_8004D080(s16 bank, s16 program, ProgramAttributes *result) {
    s32 offset;
    ProgramAttributes *last;
    if (D_8005E578[bank] == 1) {
        func_80050728(bank, program);
        offset = program * 16;
        result->tones = ((ProgramAttributes *)(offset + (u32)D_8005CFCC))->tones;
        result->volume = ((ProgramAttributes *)(offset + (u32)D_8005CFCC))->volume;
        result->priority = ((ProgramAttributes *)(offset + (u32)D_8005CFCC))->priority;
        result->mode = ((ProgramAttributes *)(offset + (u32)D_8005CFCC))->mode;
        result->pan = ((ProgramAttributes *)(offset + (u32)D_8005CFCC))->pan;
        last = (ProgramAttributes *)(offset + (u32)D_8005CFCC);
        result->attributes = last->attributes;
        return 0;
    }
    return -1;
}
