#include "common.h"

/* GCC_VERSION: 2.6.3 */
typedef struct {u8 pad00[8];void (*dispatch08)(s32,s32,s32,s32);s32 word0C;u8 pad10[8];s32 word18,word1C,word20;u32 word24,word28;void (*callback2C)(s32 *,s32);} Api;
extern Api *D_80054A64;
void func_800402C8(const char *,s32);
extern s32 (*D_80054A68)(const char *,...);
extern u8 D_80054A6E;
extern u8 D_80054B28[];

s32 *func_800406C8(s32 *arg0, s32 arg1) {
    if ((u8) D_80054A6E >= 2U) {
        D_80054A68(D_800112D8, arg0, arg1);
    }
    D_80054A64->callback2C(arg0, arg1);
    *arg0 = (s32) D_80054B28 & 0xFFFFFF;
    return arg0;
}
