/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "resource.h"

void *BIOS_MemSet(void *, s32, s32);
u8 Ns_AlphaNumChar(s32);
s32 Ns_FileOpen(s32 *, s32);
s32 Math_Randb(s32);

extern s32 gp_pbak_mode;
/* Unsized storage views retain the native absolute addressing. Only the
 * mode word above is accessed through gp in this function. */
extern s32 g_ns[];
extern s32 D_8005C54C[];

void Pbak_Choose(s32 *resource_id)
{
    u8 name[8];
    s32 count = Ns_FileOpen(&g_ns[0], 19);

    __builtin_memcpy(name, D_800564C0, 6);
    BIOS_MemSet(name + 6, 0, 2);
    if (count == 0) {
        s32 mode = gp_pbak_mode;

        *resource_id = 0x6396347F;
        if (mode != 25)
            D_800618D0 = 0;
    } else {
        name[2] = Math_Randb(count) + 0x30;
        name[3] = Ns_AlphaNumChar(D_8005C52C[0]);
        *resource_id = Ns_StringToEID(name);
        D_8005C54C[0] = -1;
        D_80061A30 = 3;
    }
}
