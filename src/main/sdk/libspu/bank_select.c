/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
extern u8 *D_80057E70[];
extern u8 *D_80057EB0[];
extern u8 *D_8005CFDC;

s32 SpuVmVSetUp(s16 arg0, s16 arg1) {
    u8 *temp_a0, *master;

    if ((u16)arg0 >= 16 || g_midi_tracks[arg0] != 1 || arg1 >= D_8005CFC4) return -1;
    master = D_80057EB0[arg0];
    temp_a0 = D_80057E70[arg0];
    D_8005E559 = arg0;
    D_8005E55E = arg1;
    D_8005CFDC = master;
    D_8005CFCC = temp_a0;
    g_ns_vpage_pool = D_80057EF8[arg0];
    D_8005E55F = temp_a0[arg1 * 16 + 8];
    return 0;
}
