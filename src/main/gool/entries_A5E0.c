/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"

void SetRotMatrix(void *);
void SetLightMatrix(void *);
void RMemcpy(void *, u32, s32);
s32 *Gpu_GetCurPrimsTail(void);
void Gte_RTransformWorldsRipple(u16 *, s32, s32, s32, s32 *, void *);
void Gte_RTransformWorldsLightning(u16 *, s32, s32, s32, s32 *, void *);

extern u16 *gp_level_entry[];
extern struct {
    u8 pad[0x10];
    u8 *data;
} *g_pads[];
extern s32 g_view_proj[];
extern s32 g_draw_stamp[];

extern s32 gp_next_lid[];

void Gfx_TransformWorldsRipple(s32 arg0)
{
    s32 i;
    s32 val;

    if (arg0 == 0) {
        for (i = 0; i < 16; i++) {
            D_800567B8[i] = ((D_80056478 + 1) / 8) * i - D_80056478;
        }
        return;
    }
    if (*gp_level_entry[0] != 0) {
        if (gp_next_lid[0] == 0) {
            for (i = 0; i < 16; i++) {
                val = D_800567B8[i] + D_80056474;
                D_800567B8[i] = val;
                if (val > D_80056478) {
                    val = -D_80056478 + 1;
                    D_800567B8[i] = val;
                }
            }
        }
        for (i = 0; i < 16; i++) {
            val = D_800567B8[i];
            ((s32 *)0x1F800048)[i] = val >= 0 ? val : -val;
        }
        SetRotMatrix(g_m_view);
        SetLightMatrix(g_m_view + 0x110);
        RMemcpy(g_pads[0]->data + 4, 0x1F800100, 0x100);
        Gte_RTransformWorldsRipple(gp_level_entry[0], arg0, 0x800 - (g_view_proj[0] / 2), g_draw_stamp[0], Gpu_GetCurPrimsTail(), D_80051774);
    }
}

void Gfx_TransformWorldsLightning(s32 arg0)
{
    if (*gp_level_entry[0] != 0) {
        SetRotMatrix(g_m_view);
        SetLightMatrix(g_m_view + 0x110);
        RMemcpy(g_pads[0]->data + 4, 0x1F800100, 0x100);
        *(s32 *)0x1F800048 = gp_fade_step << 4;
        *(s32 *)0x1F80004C = D_80056444 << 4;
        *(s32 *)0x1F800050 = D_80056448 << 4;
        *(s32 *)0x1F800054 = gp_ripple_amp;
        *(s32 *)0x1F800058 = gp_ripple_freq << 4;
        *(s32 *)0x1F80005C = D_80056454 << 4;
        *(s32 *)0x1F800060 = D_80056458 << 4;
        *(s32 *)0x1F800064 = gp_lightning_state;
        Gte_RTransformWorldsLightning(gp_level_entry[0], arg0, 0x800 - (g_view_proj[0] / 2), g_draw_stamp[0], Gpu_GetCurPrimsTail(), D_80051774);
    }
}

