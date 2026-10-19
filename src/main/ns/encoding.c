#include "common.h"

/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */

/* Character lookup and decoding for the 64-character resource-name alphabet. */

extern s32 gp_pause_B_pressed;

char *Ns_GetFilename2(s32, u32, s32, s32);
s32 sprintf(char *, const char *, ...);

u8 Ns_AlphaNumChar(s32 index)
{
    return D_80051728[index];
}

s32 Ns_AlphaNumIndex(s32 ch)
{
    s32 index;
    for (index = 0; index < 0x40; index++) {
        if (D_80051728[index] == (ch & 0xFF))
            return index;
    }
    if ((ch & 0xFF) == 0x2D)
        return 0x63;
    return -0xE;
}

char *Ns_GetFilename(s32 a, u32 b)
{
    return Ns_GetFilename2(a, b, 0, 0);
}

char *Ns_GetFilename2(s32 type, u32 id, s32 arg2, s32 arg3)
{
    switch (type) {
    case 0:
        if (gp_pause_B_pressed != 0) {
            sprintf(D_80056738, D_80010000, id >> 4, id);
        } else {
            sprintf(D_80056738, D_80010010, D_80010020, D_80010038, id);
        }
        break;
    case 1:
        if (gp_pause_B_pressed != 0) {
            sprintf(D_80056738, D_80010044, id >> 4, id);
        } else {
            sprintf(D_80056738, D_80010054, D_80010020, D_80010038, id);
        }
        break;
    default:
        return (char *)-0xE;
    }
    return D_80056738;
}
