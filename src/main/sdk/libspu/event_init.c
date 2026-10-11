#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Register the SPU callback and enable its event once. */
extern s32 D_80055DA8,D_80055948,D_800559A0;
void func_8003E1F8(void);
void func_800466A0(void);
void func_800470FC(void (*callback)(void));
s32 func_8003E1A8(u32,s32,s32,s32);
void func_8003E1D8(s32);
void func_8003E208(void);
void func_80047078(void) {
    if (!D_80055DA8) {
        D_80055DA8 = 1;
        func_8003E1F8();
        D_80055948 = 0;
        func_800470FC(func_800466A0);
        D_800559A0 = func_8003E1A8(0xf0000009,32,0x2000,0);
        func_8003E1D8(D_800559A0);
        func_8003E208();
    }
}
