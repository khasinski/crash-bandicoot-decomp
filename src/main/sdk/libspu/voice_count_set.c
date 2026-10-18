/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
extern s32 D_80056274;

u8 func_800507EC(s32 count) {
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
    D_8005E340 = count;
    voice = D_8005E340;
    if (voice < 0x18) {
        do {
            bit = 1 << voice;
            voice += 1;
            D_80056274 |= bit;
        } while (voice < 0x18);
    }
    return D_8005E340;
}
