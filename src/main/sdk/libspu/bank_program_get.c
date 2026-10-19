/* GCC_VERSION: 2.5.7 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
/* GCC_CPU: r4000 */

s32 SsUtGetProgAtr(s16 bank, s16 program, ProgramAttributes *result) {
    s32 offset;
    ProgramAttributes *last;
    if (g_midi_tracks[bank] == 1) {
        SpuVmVSetUp(bank, program);
        offset = program * 16;
        result->tones = ((ProgramAttributes *)(offset + (u32)g_vab_cur_prog_table))->tones;
        result->volume = ((ProgramAttributes *)(offset + (u32)g_vab_cur_prog_table))->volume;
        result->priority = ((ProgramAttributes *)(offset + (u32)g_vab_cur_prog_table))->priority;
        result->mode = ((ProgramAttributes *)(offset + (u32)g_vab_cur_prog_table))->mode;
        result->pan = ((ProgramAttributes *)(offset + (u32)g_vab_cur_prog_table))->pan;
        last = (ProgramAttributes *)(offset + (u32)g_vab_cur_prog_table);
        result->attributes = last->attributes;
        return 0;
    }
    return -1;
}
