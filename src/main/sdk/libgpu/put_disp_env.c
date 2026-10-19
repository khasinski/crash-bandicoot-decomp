#include "common.h"
#include "gpu.h"

/* GCC_VERSION: 2.6.3 */

/* --- PutDispEnv --- */



typedef struct {
    u8 version;
    volatile u8 mode;
    u8 debug;
    u8 reverse;
    s16 w;
    s16 h;
    volatile s32 active;
    void (* volatile callback)(void);
} GpuState;

extern GpuState g_gpu_mode;

typedef struct {
    u8 debug;
    u8 pad[15];
} GpuDebugState;
extern volatile GpuDebugState g_gpu_debug_level;

typedef struct {
    u8 reverse;
    u8 pad[15];
} GpuReverseState;
extern volatile GpuReverseState D_80054A6F;

extern volatile GpuDisplayEnv D_80054AD8;

s32 GetVideoMode(void);
s32 get_dx(GpuRect *rect);
void *BIOS_MemCpy(void *, void *, s32);

#define CLAMP(val, min, max) ((val) < (min) ? (min) : ((val) > (max) ? (max) : (val)))

GpuDisplayEnv *PutDispEnv(GpuDisplayEnv *env)
{
    u32 mode;
    s32 hx1, hx2, vy1, vy2;

    mode = 0x08000000;
    if (g_gpu_debug_level.debug >= 2) {
        g_gpu_ot_status(D_80011338, env);
    }

    g_gpu_ctl->ctl10(((u32)(g_gpu_mode.version - 1) < 2)
        ? ((((env->display.y & 0xFFF) << 12) | (get_dx(&env->display) & 0xFFF)) | 0x05000000)
        : ((((env->display.y & 0x3FF) << 10) | (env->display.x & 0x3FF)) | 0x05000000));

    if (D_80054AD8.screen.x != env->screen.x ||
        D_80054AD8.screen.y != env->screen.y ||
        D_80054AD8.screen.w != env->screen.w ||
        D_80054AD8.screen.h != env->screen.h) {
        env->pad12 = GetVideoMode();
        hx1 = 0x260 + env->screen.x * 10;
        vy1 = env->screen.y + (env->pad12 ? 0x13 : 0x10);
        hx2 = hx1 + (env->screen.w ? env->screen.w * 10 : 0xA00);
        vy2 = vy1 + (env->screen.h ? env->screen.h : 0xF0);

        hx1 = CLAMP(hx1, 0x1F4, 0xCDA);
        hx2 = CLAMP(hx2, hx1 + 0x50, 0xCDA);
        vy1 = CLAMP(vy1, 0x10, env->pad12 ? 0x136 : 0x100);
        vy2 = CLAMP(vy2, vy1 + 2, env->pad12 ? 0x138 : 0x102);

        g_gpu_ctl->ctl10(0x06000000 | ((hx2 & 0xFFF) << 12) | (hx1 & 0xFFF));
        g_gpu_ctl->ctl10(0x07000000 | ((vy2 & 0x3FF) << 10) | (vy1 & 0x3FF));
    }

    if (*(s32 *)&D_80054AD8.interlaced != *(s32 *)&env->interlaced ||
        D_80054AD8.display.x != env->display.x ||
        D_80054AD8.display.y != env->display.y ||
        D_80054AD8.display.w != env->display.w ||
        D_80054AD8.display.h != env->display.h) {
        s32 small_h;

        env->pad12 = GetVideoMode();
        if (env->pad12 == 1) {
            mode |= 0x08;
        }
        if (env->rgb24) {
            mode |= 0x10;
        }
        if (env->interlaced) {
            mode |= 0x20;
        }
        if (D_80054A6F.reverse) {
            mode |= 0x80;
        }
        if (env->display.w >= 0x119) {
            if (env->display.w < 0x161) {
                mode |= 0x01;
            } else if (env->display.w < 0x191) {
                mode |= 0x40;
            } else if (env->display.w < 0x231) {
                mode |= 0x02;
            } else {
                mode |= 0x03;
            }
        }
        small_h = env->display.h < (env->pad12 ? 0x121 : 0x101);
        if (!small_h) {
            mode |= 0x24;
        }
        g_gpu_ctl->ctl10(mode);
    }

    BIOS_MemCpy(&D_80054AD8, env, 0x14);
    return env;
}

