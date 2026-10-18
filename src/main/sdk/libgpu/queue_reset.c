#include "common.h"

/* GCC_VERSION: 2.6.3 */

s32 func_8003E870(s32);
s32 func_80042A04(s32);
void *func_80042AE0(void *, s32, u32);
extern volatile u32 *D_80054B40;
extern volatile u32 *D_80054B4C;

extern s32 D_80054B70;
/* The queue consumer callback also updates this index. */

extern u8 D_80057098[0x100];
extern u8 D_8005E74C[0x1800];

/* Reset queue indices and hardware, then restore interrupt state. */
s32 func_800425E0(s32 arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_v0;

    temp_v0 = func_8003E870(0);
    D_80054B74 = 0;
    D_80054B80 = temp_v0;
    D_80054B70 = D_80054B74;
    temp_v1 = arg0 & 7;
    switch (temp_v1) {                              /* irregular */
    case 0:
        *D_80054B4C = 0x401;
        *D_80054B5C |= 0x800;
        *D_80054B40 = 0;
        func_80042AE0(D_80057098, 0, 0x100);
        func_80042AE0(D_8005E74C, 0, 0x1800);
        break;
    case 1:
        *D_80054B4C = 0x401;
        *D_80054B5C |= 0x800;
        *D_80054B40 = 0x02000000;
        *D_80054B40 = 0x01000000;
        break;
    }
    func_8003E870(D_80054B80);
    if (!(arg0 & 7)) {
        var_v0 = func_80042A04(arg0);
    } else {
        var_v0 = 0;
    }
    return var_v0;
}
