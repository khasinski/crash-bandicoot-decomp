#include "gpu.h"

/* GCC_VERSION: 2.6.3 */

/* Submit the drawing packet and retain its 92-byte environment snapshot. */
typedef struct {GpuDrawEnv env;u32 packet[16];} Drawing;
typedef struct {u8 pad00[8];s32 (*dispatch08)(s32,void *,s32,s32);u8 pad0C[12];s32 word18;} Api;
extern Api *D_80054A64;
extern s32 (*D_80054A68)(const char *,...);
typedef struct {u8 debug;u8 pad01[13];u8 drawing[sizeof(Drawing)];} GpuState;
extern GpuState D_80054A6E;
extern void *BIOS_MemCpy(void *,void *,s32);
extern void func_800410AC(u32 *,Drawing *);
extern const char D_80011304[];
extern const char D_8001131C[];
void *func_80040834(Drawing *arg0) {
    u32 *temp_s0;
    GpuState *state = &D_80054A6E;

    if (state->debug >= 2U) {
        D_80054A68(D_80011304, arg0);
    }
    temp_s0 = arg0->packet;
    func_800410AC(temp_s0, arg0);
    arg0->packet[0] = (s32) (arg0->packet[0] | 0xFFFFFF);
    D_80054A64->dispatch08(D_80054A64->word18, temp_s0, 0x40, 0);
    BIOS_MemCpy(state->drawing, arg0, 0x5C);
    return arg0;
}

void func_800408F8(s32 arg0, Drawing *arg1) {
    u32 *temp_s0;
    GpuState *state = &D_80054A6E;

    if (state->debug >= 2U) {
        D_80054A68(D_8001131C, arg0, arg1);
    }
    temp_s0 = arg1->packet;
    func_800410AC(temp_s0, arg1);
    arg1->packet[0] = (s32) ((arg1->packet[0] & 0xFF000000) | (arg0 & 0xFFFFFF));
    D_80054A64->dispatch08(D_80054A64->word18, temp_s0, 0x40, 0);
    BIOS_MemCpy(state->drawing, arg1, 0x5C);
}
