/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"
s32 func_80043498(s32, u8 *);
s32 func_80043668(u8, u8 *);
u8 *func_80043A24(s32, u8 *);
extern s32 D_80056410;
extern void *D_8005CFAC[];
extern u32 D_8005E03C[][3];
void func_80013798(s32 index)
{
    u8 position[3];
    if (D_80056410 != 0 && D_8005CFAC[0] == NULL && func_80043498(1, NULL) == 0) {
        func_80043A24(D_8005E03C[index][0] & 0x7FFFFF, position);
        func_80043668(0x15, position);
    }
}
