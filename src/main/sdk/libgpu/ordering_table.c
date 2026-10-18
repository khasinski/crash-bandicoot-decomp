/* GCC_VERSION: 2.6.3 */
#include "gpu.h"
extern u8 D_80054A6E;
extern s32 (*D_80054A68)(const char *, ...);

extern u32 D_80054B28;

u32 *func_80040610(u32 *ot,s32 count) {
    if (D_80054A6E >= 2) D_80054A68(D_800112C0,ot,count);
    count--;
    if (count) {
        u32 address_mask = 0x00ffffff;
        u32 length_mask = 0xff000000;
        do {
            u32 *next = ot + 1;
            u32 tag;
            count--;
            ((u8 *)ot)[3] = 0;
            tag = *ot;
            tag &= length_mask;
            *ot = tag | ((u32)next & address_mask);
            ot = next;
        } while (count);
    }
    *ot = (u32)&D_80054B28 & 0x00ffffff;
    return ot;
}
