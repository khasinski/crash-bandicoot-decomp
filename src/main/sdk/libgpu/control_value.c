#include "common.h"

/* GCC_VERSION: 2.6.3 */
extern s32 (*D_80054A68)(const char *,...);
extern u8 D_80054A6C,D_80054A6E,D_80054A6F;
extern s32 D_80054A78;
extern const char D_80011228[];
s32 func_80040164(s32 arg0) {
    s32 temp_v0;

    if ((u8) D_80054A6E >= 2U) {
        D_80054A68(D_80011228, arg0);
    }
    temp_v0 = D_80054A78;
    D_80054A78 = arg0;
    return temp_v0;
}
