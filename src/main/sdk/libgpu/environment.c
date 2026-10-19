#include "common.h"
#include "gpu.h"

/* GCC_VERSION: 2.6.3 */

/* Initialise draw/display environments and pack the texture-page field for the active GPU mode. */

s32 GetVideoMode(void);
s32 GetGraphType(void);

GpuDrawEnv *SetDefDrawEnv(GpuDrawEnv *env, s32 x, s32 y, s32 w, s32 h)
{
    s32 mode = GetVideoMode();
    u8 draw;
    env->clip.x=x;
    env->clip.y=y;
    env->clip.w=w;
    env->texture_window.x=0;
    env->texture_window.y=0;
    env->texture_window.w=0;
    env->texture_window.h=0;
    env->r=0;
    env->g=0;
    env->b=0;
    env->dither=1;
    env->clip.h=h;
    if(mode) draw=h<0x121;
    else draw=h<0x101;
    env->draw_to_display=draw;
    env->offset_x=x;
    env->offset_y=y;
    if(GetGraphType()!=1) GetGraphType();
    env->texture_page=0xA;
    env->clear_background=0;
    return env;
}

GpuDisplayEnv *SetDefDispEnv(GpuDisplayEnv *env,s16 x,s16 y,s16 w,s32 h)
{
    env->display.x=x;
    env->display.y=y;
    env->display.w=w;
    env->screen.x=0;
    env->screen.y=0;
    env->screen.w=0;
    env->screen.h=0;
    env->rgb24=0;
    env->interlaced=0;
    env->pad13=0;
    env->pad12=0;
    env->display.h=h;
    return env;
}

s32 GetTPage(s32 depth,s32 blend,s32 x,s32 y)
{
    s32 mode;
    s32 page;
    s32 extra;
    if(GetGraphType()==1 || GetGraphType()==2) {
        mode=depth&3;
        page=(mode<<9)|((blend&3)<<7)|((y&0x300)>>3);
        extra=(x&0x3FF)>>6;
    } else {
        mode=depth&3;
        page=(mode<<7)|((blend&3)<<5)|((y&0x100)>>4)|((x&0x3FF)>>6);
        extra=(y&0x200)*4;
    }
    return page|extra;
}
