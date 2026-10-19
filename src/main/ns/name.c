#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Format an encoded resource ID, or encode five characters with the 64-character alphabet. */


s32 sprintf(char *, const char *, ...);

char *Ns_EIDValToString(s32 id)
{
    if (id & 1) {
        sprintf(D_80056728, D_8005641C, id >> 1);
    } else {
        sprintf(D_80056728, D_80056414, id);
    }
    return D_80056728;
}

s32 Ns_StringToEID(u8 *name)
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
