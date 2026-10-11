/* GCC_VERSION: 2.6.3 */
#include "common.h"
void func_8003D740(u8 *, u8 *, u32);
extern u8 D_80051728[];
extern u8 D_80056414[];
extern u8 D_80056718[];
extern s8 D_8005671D;
u8 *func_80012580(u32 id)
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
        func_8003D740(D_80056718, D_80056414, id);
    }
    return D_80056718;
}
