#include "common.h"

/* GCC_VERSION: 2.6.3 */
extern s32 (*D_80054A68)(const char *,...);
extern u8 D_80054A6C,D_80054A6E,D_80054A6F;
typedef struct {u8 pad00[0x3C];void (*callback3C)(s32);} Api;
extern Api *D_80054A64;
extern const char D_80011258[];
void func_8004025C(s32 arg0) {
    if ((u8) D_80054A6E >= 2U) {
        D_80054A68(D_80011258, arg0);
    }
    D_80054A64->callback3C(arg0);
}
