#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Shared CD read state; retain the observed load after writing mode. */
s32 func_800440EC(s32, s32);                              /* extern */
s32 func_80044640(s32, s32, s32, s32);                        /* extern */
s32 func_8004519C(void);                                /* extern */
extern s32 D_800555A0;
extern s32 D_800555A4;
extern s32 D_800555B0;

#include "cd_read_state.h"

s32 func_80045518(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v1;

    D_80055880.mode = arg2;
    temp_v1 = D_80055880.mode & 0x30;
    switch (temp_v1) {                              /* irregular */
    case 0:
        D_80055880.size = 0x200;
        break;
    case 32:
        D_80055880.size = 0x249;
        break;
    default:
        D_80055880.size = 0x246;
        break;
    }
    D_80055880.count = arg0;
    D_80055880.buffer = arg1;
    D_80055880.state = 8;
    D_80055880.word20 = D_800555A0;
    D_80055880.word24 = D_800555A4;
    if (D_800555B0 & 0xE0) {
        func_80044640(9, 0, 0, 0);
    }
    func_800440EC(0, 0);
    return -(func_8004519C() < 1);
}
