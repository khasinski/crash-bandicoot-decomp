#include "common.h"

/* GCC_VERSION: 2.6.3 */

s32 BIOS_Printf(const char *, ...);
void ResetCallback(void);
u8 _reset(s32);
void *memset(void *, s32, u32);
void GPU_cw(u32);

extern u8 g_gpu_mode[];
extern u8 D_80054A6D;
extern u8 g_gpu_debug_level;
extern u16 D_80054A70;
extern u16 D_80054A72;

/* Reset the GPU state and cached environments, or invoke the driver reset. */
s32 ResetGraph(s32 requested)
{
    s32 operation = requested & 7;
    if (operation == 0 || operation == 3) {
        u8 *state = g_gpu_mode;
        BIOS_Printf(D_8001119C, D_80054A24, state);
        memset(state, 0, 0x80);
        ResetCallback();
        GPU_cw((u32)g_gpu_ctl & 0xFFFFFF);
        state[0] = _reset(operation != 0);
        D_80054A6D = 1;
        D_80054A70 = *(u16 *)(D_80054AEC + state[0] * 4);
        D_80054A72 = *(u16 *)(D_80054B00 + state[0] * 4);
        memset(state + 0x10, -1, 0x5C);
        memset(state + 0x6C, -1, 0x14);
        return state[0];
    }
    if (g_gpu_debug_level >= 2) g_gpu_ot_status(D_800111BC, requested);
    return g_gpu_ctl->reset34(1);
}
