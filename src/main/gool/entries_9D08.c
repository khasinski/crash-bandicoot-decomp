#include "common.h"
extern s32 g_draw_stamp;

/* GCC_VERSION: 2.6.3 */


extern u16 *gp_level_entry;
extern struct {
    u8 pad[0x10];
    u8 *data;
} *g_pads;
extern s32 g_view_proj;

extern struct {
    s32 unk0;
    s32 type;
} *g_ns_page_pool;

void Gfx_TransformWorlds(s32 arg0)
{
    if (*gp_level_entry != 0) {
        SetRotMatrix(g_m_view);
        SetLightMatrix(g_m_view + 0x110);
        RMemcpy(g_pads->data + 4, 0x1F800100, 0x100);
        Gte_RTransformWorlds(gp_level_entry, arg0, 0x800 - (g_view_proj / 2), g_draw_stamp, Gpu_GetCurPrimsTail(), g_wgeo_tex_anim_masks);
    }
}

