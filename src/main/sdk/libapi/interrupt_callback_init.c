#include "common.h"

/* GCC_VERSION: 2.6.3 */
typedef void (*Callback)(void);
typedef Callback (*Registrar)(s32,Callback);
Callback func_8003E724(s32,Callback);
extern void func_8003EEAC(void),func_8003EFCC(void);
extern Callback func_8003EF24(s32,Callback),func_8003F150(s32,Callback);
extern void func_8003EF50(Callback *,s32),func_8003F1F8(Callback *,s32);
extern Callback D_800549D0[],D_800549FC[];
extern volatile s32 *D_800549F4,*D_800549F8;
Registrar func_8003EF7C(void) {
    func_8003F1F8(D_800549FC, 8);
    *D_800549F8 = 0;
    func_8003E724(3, &func_8003EFCC);
    return &func_8003F150;
}
