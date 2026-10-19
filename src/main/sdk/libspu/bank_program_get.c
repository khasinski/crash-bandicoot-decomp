/* GCC_VERSION: 2.5.7 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
/* GCC_CPU: r4000 */
s32 SpuVmVSetUp(s16, s16);

typedef struct {
    u8 tones, volume, priority, mode, pan, unused;
    u16 attributes;
    u8 tail[8];
} ProgramAttributes;
s32 SsUtGetProgAtr(s16 bank, s16 program, ProgramAttributes *result) {
    s32 offset;
    ProgramAttributes *last;
    if (g_midi_tracks[bank] == 1) {
        SpuVmVSetUp(bank, program);
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
