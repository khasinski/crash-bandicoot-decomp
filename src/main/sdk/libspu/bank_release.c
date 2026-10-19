/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"

void SpuFree(u32);


void SsVabClose(s32 requested)
{
    s16 index;
    if ((u16)requested < 16) {
        index = requested;
        if (g_midi_tracks[index] == 1) {
            SpuFree(D_80060CF0[index]);
            g_midi_tracks[index] = 0;
            D_80060CE8--;
        }
    }
}
