/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

u8 SsSetReservedVoice(s32 count) {
    s32 bit;
    u32 requested;
    s32 voice;

    requested = count & 0xFF;
    if (requested >= 25) {
        return 255;
    }
    if (requested == 0) {
        return 255;
    }
    gp_spawn_count = count;
    voice = gp_spawn_count;
    if (voice < 0x18) {
        do {
            bit = 1 << voice;
            voice += 1;
            D_80056274 |= bit;
        } while (voice < 0x18);
    }
    return gp_spawn_count;
}
