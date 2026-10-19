#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Update GPU debug and mode bytes, returning their previous values. */
extern u8 g_gpu_mode;
typedef struct {u8 debug;u8 pad01[13];u8 drawing[92];u8 display[20];} GpuState;
extern GpuState g_gpu_debug_level;
typedef struct {u8 reverse;u8 pad01[12];u8 drawing[92];u8 display[20];} GpuReverseState;
extern GpuReverseState D_80054A6F;


u8 SetGraphReverse(s32 requested) {
    GpuReverseState *state = &D_80054A6F;
    u8 previous = state->reverse;
    if (g_gpu_debug_level.debug >= 2) {
        g_gpu_ot_status(D_800111D0, requested);
    }
    state->reverse = requested;
    g_gpu_ctl->ctl10(g_gpu_ctl->ctl28(8) | (state->reverse ? 0x08000080 : 0x08000000));
    if (g_gpu_mode == 2) {
        g_gpu_ctl->ctl10(D_80054A6F.reverse ? 0x20000501 : 0x20000504);
    }
    return previous;
}

u8 SetGraphDebug(u8 arg0) {
    u8 temp_s0;
    GpuState *state = &g_gpu_debug_level;

    temp_s0 = state->debug;
    state->debug = arg0;
    if (arg0 & 0xFF) {
        g_gpu_ot_status(D_800111E8, state->debug, g_gpu_mode, D_80054A6F.reverse);
    }
    return temp_s0;
}

typedef struct {u8 mode,debug;u8 pad02[12];u8 drawing[92];u8 display[20];} GpuModeState;
extern GpuModeState D_80054A6D;
s32 DMACallback(s32,s32);

u8 SetGraphQueue(s32 requested) {
    GpuModeState *state = &D_80054A6D;
    u8 previous = state->mode;
    if (g_gpu_debug_level.debug >= 2) g_gpu_ot_status(D_80011214,requested);
    if (requested != state->mode) {
        g_gpu_ctl->reset34(1);
        state->mode = requested;
        DMACallback(2,0);
    }
    return previous;
}
