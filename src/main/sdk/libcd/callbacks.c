#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Clear callback state and install the CD interrupt handler. */
s32 func_8003E6F4(void);
extern s32 func_8003E724(s32, void (*)(void));
extern s32 D_800555A0;
extern s32 D_800555A4;
extern s32 D_800555B0;
extern s32 D_800555B4;
extern s32 D_80055880[10];
void func_80045B24(void);

void func_80044E1C(void) {
    s32 *var_v1;
    s32 var_v0;

    var_v1 = D_80055880;
    var_v0 = 9;
    D_800555A4 = 0;
    D_800555A0 = 0;
    D_800555B4 = 0;
    D_800555B0 = 0;
    do {
        *var_v1 = 0;
        var_v0 -= 1;
        var_v1++;
    } while (var_v0 != -1);
    func_8003E6F4();
    func_8003E724(2, &func_80045B24);
}
