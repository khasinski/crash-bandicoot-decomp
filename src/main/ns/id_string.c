/* GCC_VERSION: 2.6.3 */
#include "common.h"
void sprintf(u8 *, u8 *, u32);

u8 *Ns_EIDToString(u32 id)
{
    s32 index;
    if (id & 1) {
        D_8005671D = 0;
        id >>= 1;
        index = 4;
        do {
            D_80056718[index] = D_80051728[id & 0x3F];
            index--;
            id >>= 6;
        } while (index >= 0);
    } else {
        sprintf(D_80056718, D_80056414, id);
    }
    return D_80056718;
}
