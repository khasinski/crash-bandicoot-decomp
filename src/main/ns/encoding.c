#include "common.h"

/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */

/* Character lookup and decoding for the 64-character resource-name alphabet. */

extern u8 D_80051728[];
extern s32 D_80056410;
extern char D_80056738[];
extern const char D_80010000[];
extern const char D_80010010[];
extern const char D_80010020[];
extern const char D_80010038[];
extern const char D_80010044[];
extern const char D_80010054[];
extern char *func_800128A4(s32, u32, s32, s32);
extern s32 func_8003D740(char *, const char *, ...);

u8 func_80012820(s32 index)
{
    return D_80051728[index];
}

s32 func_80012834(s32 ch)
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

char *func_80012880(s32 a, u32 b)
{
    return func_800128A4(a, b, 0, 0);
}

char *func_800128A4(s32 type, u32 id, s32 arg2, s32 arg3)
{
    switch (type) {
    case 0:
        if (D_80056410 != 0) {
            func_8003D740(D_80056738, D_80010000, id >> 4, id);
        } else {
            func_8003D740(D_80056738, D_80010010, D_80010020, D_80010038, id);
        }
        break;
    case 1:
        if (D_80056410 != 0) {
            func_8003D740(D_80056738, D_80010044, id >> 4, id);
        } else {
            func_8003D740(D_80056738, D_80010054, D_80010020, D_80010038, id);
        }
        break;
    default:
        return (char *)-0xE;
    }
    return D_80056738;
}
