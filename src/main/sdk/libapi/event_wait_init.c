#include "common.h"

/* GCC_VERSION: 2.6.3 */
void func_8003E4C0(s32, s32 *);                          /* extern */
void func_8003E4E0(s32);                                 /* extern */
void func_8003E6F4();                                  /* extern */
extern s32 D_80057054;
extern s32 D_8005E33C;

void func_8003E410(s32 arg0) {
    D_8005E33C = arg0;
    D_80057054 = -1;
    func_8003E6F4();
    func_8003E4C0(0x20000001, &D_80057054);
    func_8003E4E0(0);
}
