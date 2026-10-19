/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"
extern s32 gp_pause_B_pressed;

extern u32 g_file_map[][3];
void Ns_CdSeek(s32 index)
{
    u8 position[3];
    if (gp_pause_B_pressed != 0 && g_ns_active_cd_slot[0] == NULL && CdSync(1, NULL) == 0) {
        CdIntToPos(g_file_map[index][0] & 0x7FFFFF, position);
        CdControlF(0x15, position);
    }
}
