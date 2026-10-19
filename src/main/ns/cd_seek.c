/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"
s32 CdSync(s32, u8 *);
s32 CdControlF(u8, u8 *);
u8 *CdIntToPos(s32, u8 *);
extern s32 gp_pause_B_pressed;

extern u32 g_file_map[][3];
void Ns_CdSeek(s32 index)
{
    u8 position[3];
    if (gp_pause_B_pressed != 0 && D_8005CFAC[0] == NULL && CdSync(1, NULL) == 0) {
        CdIntToPos(g_file_map[index][0] & 0x7FFFFF, position);
        CdControlF(0x15, position);
    }
}
