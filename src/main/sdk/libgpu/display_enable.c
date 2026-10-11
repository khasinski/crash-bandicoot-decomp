#include "gpu.h"

/* GCC_VERSION: 2.6.3 */

/* Clear the cached display environment when disabling GPU output. */
typedef struct {u8 debug;u8 pad01[13];u8 drawing[92];u8 display[20];} GpuState;
typedef struct {u8 pad00[16];void (*command10)(u32);} GpuApi;
extern GpuState D_80054A6E;
extern GpuApi *D_80054A64;
extern s32 (*D_80054A68)(const char *,...);
extern const char D_80011244[];
void func_80042AE0(void *,s32,s32);
void func_800401C0(s32 enabled) {
    GpuState *state = &D_80054A6E;
    u32 command;
    GpuApi *api;
    u8 *display;
    if (state->debug >= 2) D_80054A68(D_80011244,enabled);
    display = state->display;
    if (!enabled) func_80042AE0(display,-1,20);
    api = D_80054A64;
    command = 0x03000001;
    if (enabled) command = 0x03000000;
    api->command10(command);
}
