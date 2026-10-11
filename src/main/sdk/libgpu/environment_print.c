#include "gpu.h"

/* GCC_VERSION: 2.6.3 */

s32 func_80040144(void);
extern const char D_80011098[];
extern const char D_800110C0[];
extern const char D_800110D8[];
extern const char D_800110E8[];
extern const char D_80011100[];
extern const char D_8001110C[];
extern s32 (*D_80054A68)(const char *, ...);

/* Print the draw environment and hardware-specific texture-page fields. */
void func_8003FB94(GpuDrawEnv *arg0) {
    u16 temp_v0;
    u16 temp_v0_2;

    D_80054A68(D_800110C0, arg0->clip.x, arg0->clip.y, arg0->clip.w, (s32) arg0->clip.h);
    D_80054A68(D_800110D8, arg0->offset_x, arg0->offset_y);
    D_80054A68(D_800110E8, arg0->texture_window.x, arg0->texture_window.y, arg0->texture_window.w, (s32) arg0->texture_window.h);
    D_80054A68(D_80011100, (s16) arg0->dither);
    D_80054A68(D_8001110C, (s16) arg0->draw_to_display);
    if ((func_80040144() == 1) || (func_80040144() == 2)) {
        temp_v0 = arg0->texture_page;
        D_80054A68(D_80011098, (temp_v0 >> 9) & 3, (temp_v0 >> 7) & 3, (temp_v0 << 6) & 0x7C0, (temp_v0 * 8) & 0x300);
        return;
    }
    temp_v0_2 = arg0->texture_page;
    D_80054A68(D_80011098, (temp_v0_2 >> 7) & 3, (temp_v0_2 >> 5) & 3, (temp_v0_2 << 6) & 0x7C0, ((temp_v0_2 * 0x10) & 0x100) + ((temp_v0_2 >> 2) & 0x200));
}

extern const char D_80011118[], D_80011134[], D_80011150[], D_8001115C[];
/* Print the display and screen rectangles and display flags. */
void func_8003FD14(GpuDisplayEnv *env)
{
    D_80054A68(D_80011118, env->display.x, env->display.y, env->display.w, env->display.h);
    D_80054A68(D_80011134, env->screen.x, env->screen.y, env->screen.w, env->screen.h);
    D_80054A68(D_80011150, env->interlaced);
    D_80054A68(D_8001115C, env->rgb24);
}
