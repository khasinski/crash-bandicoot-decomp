#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Update GPU debug and mode bytes, returning their previous values. */
extern s32 (*D_80054A68)(const char *,...);
extern u8 D_80054A6C;
typedef struct {u8 debug;u8 pad01[13];u8 drawing[92];u8 display[20];} GpuState;
extern GpuState D_80054A6E;
typedef struct {u8 reverse;u8 pad01[12];u8 drawing[92];u8 display[20];} GpuReverseState;
extern GpuReverseState D_80054A6F;
extern const char D_800111D0[];
extern const char D_800111E8[];

typedef struct {
    u8 pad00[0x10];
    void (*ctl10)(u32);
    u8 pad14[0x14];
    u32 (*ctl28)(s32);
    u8 pad2C[0x08];
    void (*reset34)(s32);
} GpuApi;
extern GpuApi *D_80054A64;

u8 func_8003FF18(s32 requested) {
    GpuReverseState *state = &D_80054A6F;
    u8 previous = state->reverse;
    if (D_80054A6E.debug >= 2) {
        D_80054A68(D_800111D0, requested);
    }
    state->reverse = requested;
    D_80054A64->ctl10(D_80054A64->ctl28(8) | (state->reverse ? 0x08000080 : 0x08000000));
    if (D_80054A6C == 2) {
        D_80054A64->ctl10(D_80054A6F.reverse ? 0x20000501 : 0x20000504);
    }
    return previous;
}

u8 func_8004002C(u8 arg0) {
    u8 temp_s0;
    GpuState *state = &D_80054A6E;

    temp_s0 = state->debug;
    state->debug = arg0;
    if (arg0 & 0xFF) {
        D_80054A68(D_800111E8, state->debug, D_80054A6C, D_80054A6F.reverse);
    }
    return temp_s0;
}

extern const char D_80011214[];
typedef struct {u8 mode,debug;u8 pad02[12];u8 drawing[92];u8 display[20];} GpuModeState;
extern GpuModeState D_80054A6D;
s32 func_8003E754(s32,s32);

u8 func_80040098(s32 requested) {
    GpuModeState *state = &D_80054A6D;
    u8 previous = state->mode;
    if (D_80054A6E.debug >= 2) D_80054A68(D_80011214,requested);
    if (requested != state->mode) {
        D_80054A64->reset34(1);
        state->mode = requested;
        func_8003E754(2,0);
    }
    return previous;
}
