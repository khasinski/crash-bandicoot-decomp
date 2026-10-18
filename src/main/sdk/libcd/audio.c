#include "cd_audio.h"

/* GCC_VERSION: 2.6.3 */

/* Initialise SPU CD mixing and route CD stereo output. */

s32 func_80044D28(void) {
    u8 volume[4];
    if (D_80055878[0x1B8/2] == 0) {
        if (D_80055878[0x1BA/2] == 0) {
            D_80055878[0x180/2] = 0x3FFF;
            D_80055878[0x182/2] = 0x3FFF;
        }
    }
    D_80055878[0x1B0/2] = 0x3FFF;
    D_80055878[0x1B2/2] = 0x3FFF;
    D_80055878[0x1AA/2] = 0xC001;
    volume[2] = 0x80;
    volume[0] = 0x80;
    volume[3] = 0;
    volume[1] = 0;
    return CD_WriteVolumeRegisters(volume);
}
