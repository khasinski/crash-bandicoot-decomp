#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Format an encoded resource ID, or encode five characters with the 64-character alphabet. */

extern u8 D_80051728[];
extern char D_80056728[];
extern char D_8005641C[];
extern char D_80056414[];
extern s32 func_8003D740(char *, const char *, ...);

char *func_80012604(s32 id)
{
    if (id & 1) {
        func_8003D740(D_80056728, D_8005641C, id >> 1);
    } else {
        func_8003D740(D_80056728, D_80056414, id);
    }
    return D_80056728;
}

s32 func_80012660(u8 *name)
{
    s32 id = 0;
    u8 *end = name + 5;
    s32 index;

    do {
        id <<= 6;
        for (index = 0; index < 0x40; index++) {
            if (D_80051728[index] == *name) {
                id |= index;
                break;
            }
        }
        name++;
    } while ((s32)name < (s32)end);
    id <<= 1;
    return id | 1;
}
