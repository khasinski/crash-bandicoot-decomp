#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Configure the CD DMA registers and poll the volatile hardware completion bit. */

extern volatile u8 *g_cd_reg0;
extern volatile u8 *D_80055870;


s32 CD_getsector(s32 arg0, s32 arg1) {
    *g_cd_reg0 = 0;
    *D_80055870 = 0x80;
    *D_800558C8 = 0x20943;
    *D_80055874 = 0x1323;
    *D_800558CC |= 0x8000;
    *D_800558D0 = arg0;
    *D_800558D4 = arg1 | 0x10000;
    *D_800558D8 = 0x11000000;
    if (*D_800558D8 & 0x01000000) {
        do {

        } while (*D_800558D8 & 0x01000000);
    }
    *D_80055874 = 0x1325;
    return 0;
}
