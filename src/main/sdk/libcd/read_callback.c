#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Consume a completed sector, advance read state and dispatch completion. */
#include "cd_read_state.h"
s32 VSync(s32);                                  /* extern */
s32 func_80044640(s32,s32,s32,s32);                        /* extern */
s32 func_8004519C(void);                                  /* extern */
s32 func_80045A34(s32,s32);                          /* extern */
extern s32 D_800555A0;
extern s32 D_800555A4;
extern void (*D_800555A8)(s32,void *);

void func_80045C04(s32 arg0, void *arg1) {
    s32 var_a0;

    if (arg0 == 1) {
        if (D_80055880.remaining > 0) {
            func_80045A34(D_80055880.cursor, D_80055880.size);
            D_80055880.cursor += D_80055880.size * 4;
            D_80055880.remaining--;
        }
    } else {
        D_80055880.remaining = -1;
    }
    D_80055880.time = VSync(-1);
    if ((D_80055880.remaining < 0) && (D_80055880.state > 0)) {
        func_8004519C();
    }
    if (D_80055880.remaining <= 0) {
        D_800555A0 = D_80055880.word20;
        D_800555A4 = D_80055880.word24;
        func_80044640(9, 0, 0, 0);
        if (D_800555A8 != NULL) {
            var_a0 = 5;
            if (D_80055880.remaining == 0) {
                var_a0 = 2;
            }
            D_800555A8(var_a0, arg1);
        }
    }
}
