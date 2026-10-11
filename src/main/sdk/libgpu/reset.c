#include "common.h"

/* GCC_VERSION: 2.6.3 */

s32 func_8003D730(const char *, ...);
void func_8003E6F4(void);
u8 func_800425E0(s32);
void *func_80042AE0(void *, s32, u32);
void func_80042B0C(u32);
extern const char D_8001119C[], D_800111BC[], D_80054A24[];
extern u8 D_80054A6C[], D_80054A6D, D_80054A6E;
extern u16 D_80054A70, D_80054A72;
extern u8 D_80054AEC[], D_80054B00[];
typedef struct {u8 reserved00[0x34];s32 (*reset34)(s32);} GpuApi;
extern GpuApi *D_80054A64;
extern s32 (*D_80054A68)(const char *, ...);
/* Reset the GPU state and cached environments, or invoke the driver reset. */
s32 func_8003FDC0(s32 requested)
{
    s32 operation = requested & 7;
    if (operation == 0 || operation == 3) {
        u8 *state = D_80054A6C;
        func_8003D730(D_8001119C, D_80054A24, state);
        func_80042AE0(state, 0, 0x80);
        func_8003E6F4();
        func_80042B0C((u32)D_80054A64 & 0xFFFFFF);
        state[0] = func_800425E0(operation != 0);
        D_80054A6D = 1;
        D_80054A70 = *(u16 *)(D_80054AEC + state[0] * 4);
        D_80054A72 = *(u16 *)(D_80054B00 + state[0] * 4);
        func_80042AE0(state + 0x10, -1, 0x5C);
        func_80042AE0(state + 0x6C, -1, 0x14);
        return state[0];
    }
    if (D_80054A6E >= 2) D_80054A68(D_800111BC, requested);
    return D_80054A64->reset34(1);
}
