#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Decode CLUT coordinates for the diagnostic callback. */

extern char D_800110B0[];
extern s32 (*D_80054A68)(const char *, ...);

void func_8003F6C4(s32 arg0) {
    D_80054A68(D_800110B0, (arg0 & 0x3F) * 0x10, (u32) (arg0 & 0xFFFF) >> 6);
}
