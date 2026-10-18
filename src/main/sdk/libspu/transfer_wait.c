#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Query transfer completion, or wait for the event in blocking mode. */

s32 func_8003E1C8(s32);
extern s32 D_80055914;
extern s32 D_8005594C;
extern s32 D_800559A0;

s32 func_80048A88(s32 blocking) {
    s32 completed;

    if ((D_8005594C == 1) || (D_80055914 == 1)) {
        return 1;
    }
    completed = func_8003E1C8(D_800559A0);
    if (blocking == 1) {
        if (completed == 0) {
            do {
            } while (func_8003E1C8(D_800559A0) == 0);
        }
        completed = 1;
        goto record_completion;
    }
    if (completed == 1) {
record_completion:
        D_80055914 = completed;
    }
    return completed;
}
