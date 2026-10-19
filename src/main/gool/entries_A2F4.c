#include "common.h"

/* GCC_VERSION: 2.6.3 */


typedef struct ZoneFogHeader {
    u8 pad00[0x2E8];
    s32 depth_offset;
    s32 fog_mode;
} ZoneFogHeader;

extern struct {
    u8 pad[0x10];
    ZoneFogHeader *data;
} *g_pads;

extern struct {
    s32 unk0;
    s32 type;
} *g_ns_page_pool;

void Gfx_GetFar(u32 *arg0, s32 *arg1)
{
    s32 type;
    u32 offset;
    u32 val;
    s32 flag;

    type = g_ns_page_pool->type;
    if (type == 0x14 || type == 0x16) {
        offset = g_pause_state.wordAA8 * 0xC80 + 0x64000;
        val = ((u32)g_pads->data->depth_offset - offset) >> 8;
        g_pause_state.wordAC8 = val + 0x7D0;
        flag = g_pads->data->fog_mode;
        *arg0 = val;
    } else {
        val = (g_pads->data->depth_offset - 0x32000) >> 8;
        flag = g_pads->data->fog_mode;
        if (flag == 1) {
            val -= 0x4B0;
        }
        g_pause_state.wordAC8 = val + 0x320;
        *arg0 = val;
    }
    *arg1 = flag;
}

