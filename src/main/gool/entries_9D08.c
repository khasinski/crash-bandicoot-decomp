#include "common.h"
extern s32 g_draw_stamp;

/* GCC_VERSION: 2.6.3 */

void SetRotMatrix(void *);
void SetLightMatrix(void *);
void RMemcpy(void *, u32, s32);
s32 *Gpu_GetCurPrimsTail(void);
void Gte_RTransformWorlds(u16 *, s32, s32, s32, s32 *, void *);
void Gte_RTransformWorldsFog(u16 *, s32, s32, s32, s32 *, void *);
void Gte_RTransformWorldsRipple(u16 *, s32, s32, s32, s32 *, void *);
void Gte_RTransformWorldsLightning(u16 *, s32, s32, s32, s32 *, void *);
void Gte_RTransformWorldsDark(u16 *, s32, s32, s32, s32 *, void *, u32, s32);
void Gte_RTransformWorldsDark2(u16 *, s32, s32, s32, s32 *, void *);
void *Ns_Lookup(void *);

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
        Gte_RTransformWorlds(gp_level_entry, arg0, 0x800 - (g_view_proj / 2), g_draw_stamp, Gpu_GetCurPrimsTail(), D_80051774);
    }
}

