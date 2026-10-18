/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "resource.h"

void *BIOS_MemSet(void *, s32, s32);
u8 func_80012820(s32);
s32 func_80012DCC(s32 *, s32);
s32 func_8002F778(s32);

extern s32 D_80056710;
/* Unsized storage views retain the native absolute addressing. Only the
 * mode word above is accessed through gp in this function. */
extern s32 D_8005C528[], D_8005C54C[];
extern s32 D_800618D0[], D_80061A30[];

void func_8002EABC(s32 *resource_id)
{
    u8 name[8];
    s32 count = func_80012DCC(&D_8005C528[0], 19);

    __builtin_memcpy(name, D_800564C0, 6);
    BIOS_MemSet(name + 6, 0, 2);
    if (count == 0) {
        s32 mode = D_80056710;

        *resource_id = 0x6396347F;
        if (mode != 25)
            D_800618D0[0] = 0;
    } else {
        name[2] = func_8002F778(count) + 0x30;
        name[3] = func_80012820(D_8005C52C[0]);
        *resource_id = func_80012660(name);
        D_8005C54C[0] = -1;
        D_80061A30[0] = 3;
    }
}
