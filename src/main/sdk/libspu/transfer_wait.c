#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Query transfer completion, or wait for the event in blocking mode. */

s32 TestEvent(s32);

s32 SpuIsTransferCompleted(s32 blocking) {
    s32 completed;

    if ((D_8005594C == 1) || (D_80055914 == 1)) {
        return 1;
    }
    completed = TestEvent(D_800559A0);
    if (blocking == 1) {
        if (completed == 0) {
            do {
            } while (TestEvent(D_800559A0) == 0);
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
