#include "gpu.h"

/* GCC_VERSION: 2.6.3 */

s32 GetGraphType(void);


/* Print the draw environment and hardware-specific texture-page fields. */
void DumpDrawEnv(GpuDrawEnv *arg0) {
    u16 temp_v0;
    u16 temp_v0_2;

    g_gpu_ot_status(D_800110C0, arg0->clip.x, arg0->clip.y, arg0->clip.w, (s32) arg0->clip.h);
    g_gpu_ot_status(D_800110D8, arg0->offset_x, arg0->offset_y);
    g_gpu_ot_status(D_800110E8, arg0->texture_window.x, arg0->texture_window.y, arg0->texture_window.w, (s32) arg0->texture_window.h);
    g_gpu_ot_status(D_80011100, (s16) arg0->dither);
    g_gpu_ot_status(D_8001110C, (s16) arg0->draw_to_display);
    if ((GetGraphType() == 1) || (GetGraphType() == 2)) {
        temp_v0 = arg0->texture_page;
        g_gpu_ot_status(D_80011098, (temp_v0 >> 9) & 3, (temp_v0 >> 7) & 3, (temp_v0 << 6) & 0x7C0, (temp_v0 * 8) & 0x300);
        return;
    }
    temp_v0_2 = arg0->texture_page;
    g_gpu_ot_status(D_80011098, (temp_v0_2 >> 7) & 3, (temp_v0_2 >> 5) & 3, (temp_v0_2 << 6) & 0x7C0, ((temp_v0_2 * 0x10) & 0x100) + ((temp_v0_2 >> 2) & 0x200));
}

/* Print the display and screen rectangles and display flags. */
void DumpDispEnv(GpuDisplayEnv *env)
{
    g_gpu_ot_status(D_80011118, env->display.x, env->display.y, env->display.w, env->display.h);
    g_gpu_ot_status(D_80011134, env->screen.x, env->screen.y, env->screen.w, env->screen.h);
    g_gpu_ot_status(D_80011150, env->interlaced);
    g_gpu_ot_status(D_8001115C, env->rgb24);
}
