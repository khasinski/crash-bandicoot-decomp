#include "common.h"
/* GCC_VERSION: 2.5.7 */
extern void func_8004F998(s32, s16, s16, s32);
extern s16 func_8004FF54(s32, u16 *, u16 *);

void func_8004CCDC(s16 arg0, s32 arg1, s16 arg2, s16 arg3) {
    func_8004F998(((s32)(arg1 << 16) >> 8) | arg0, arg2, arg3, 1);
}

void func_8004CD20(s16 arg0, s16 arg1, s16 arg2) {
    func_8004CCDC(arg0, 0, arg1, arg2);
}

void func_8004CD58(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    func_8004CCDC(arg0, arg1, arg2, arg3);
}

void func_8004CD94(s16 arg0, s32 arg1, u16 *arg2, u16 *arg3) {
    func_8004FF54(((s32)(arg1 << 16) >> 8) | arg0, arg2, arg3);
}
