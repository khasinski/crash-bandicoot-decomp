#include "common.h"

/* GCC_VERSION: 2.6.3 */
s32 func_800422E4(void);
void func_80042864(void);
s32 func_80042898(void);
extern volatile u32 *D_80054B40;
extern volatile u32 *D_80054B4C;
extern s32 D_80054B70;

s32 func_8004271C(s32 poll) {
    s32 pending;

    if (poll == 0) {
        func_80042864();
        while (D_80054B70 != D_80054B74) {
            func_800422E4();
            if (func_80042898() != 0) return -1;
        }
        while ((*D_80054B4C & 0x01000000) || !(*D_80054B40 & 0x04000000)) {
            if (func_80042898() != 0) return -1;
        }
        return 0;
    }
    pending = (D_80054B70 - D_80054B74) & 0x3F;
    if (pending != 0) {
        func_800422E4();
    }
    if ((*D_80054B4C & 0x01000000) || !(*D_80054B40 & 0x04000000)) {
        if (pending == 0) return 1;
        return pending;
    }
    return pending;
}
