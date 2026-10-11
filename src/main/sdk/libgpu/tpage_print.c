#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Decode a texture-page value for the diagnostic callback. */

extern s32 func_80040144(void);
extern char D_80011098[];
extern s32 (*D_80054A68)(const char *, ...);

void func_8003F5F4(s32 page) {
    u32 default_page;
    u32 mode_page;

    if ((func_80040144() == 1) || (func_80040144() == 2)) {
        mode_page = page & 0xFFFF;
        D_80054A68(D_80011098, (mode_page >> 9) & 3, (mode_page >> 7) & 3, (mode_page << 6) & 0x7C0, (mode_page * 8) & 0x300);
        return;
    }
    default_page = page & 0xFFFF;
    D_80054A68(D_80011098, (default_page >> 7) & 3, (default_page >> 5) & 3, (default_page << 6) & 0x7C0, ((default_page * 0x10) & 0x100) + ((default_page >> 2) & 0x200));
}
