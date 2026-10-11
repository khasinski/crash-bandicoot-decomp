#include "common.h"

/* GCC_VERSION: 2.6.3 */
typedef struct {u8 pad00[8];void (*dispatch08)(s32,s32,s32,s32);s32 word0C;u8 pad10[8];s32 word18,word1C,word20;u32 word24,word28;void (*callback2C)(s32 *,s32);} Api;
extern Api *D_80054A64;
extern void func_800402C8(const char *,s32);
extern s32 (*D_80054A68)(const char *,...);
extern u8 D_80054A6E;
extern u8 D_80054B28[];
extern const char D_800112F0[];
void func_800407C0(s32 arg0) {
    if ((u8) D_80054A6E >= 2U) {
        D_80054A68(D_800112F0, arg0);
    }
    D_80054A64->dispatch08(D_80054A64->word18, arg0, 0, 0);
}
