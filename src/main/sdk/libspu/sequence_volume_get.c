/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
extern s16 D_8005E56E;
extern u8 *D_80060418[];

s16 func_8004FF54(s16 arg0, u16 *arg1, u16 *arg2) {
    union { s32 channel; u16 *packed_id; } phase;
    u8 *temp_v0;

    phase.channel = (arg0 & 0xFF00) >> 8;
    temp_v0 = (phase.channel * 0xAC) + D_80060418[arg0 & 255];
    phase.packed_id = (u16 *)&D_8005E56E;
    *phase.packed_id = arg0;
    *arg1 = *(u16 *)(temp_v0 + 0x74);
    *arg2 = *(u16 *)(temp_v0 + 0x76);
    return (s16)*phase.packed_id;
}
