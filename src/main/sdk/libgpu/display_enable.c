#include "gpu.h"

/* GCC_VERSION: 2.6.3 */

/* Clear the cached display environment when disabling GPU output. */
typedef struct {u8 debug;u8 pad01[13];u8 drawing[92];u8 display[20];} GpuState;
extern GpuState g_gpu_debug_level;

void memset(void *,s32,s32);
void SetDispMask(s32 enabled) {
    GpuState *state = &g_gpu_debug_level;
    u32 command;
    GpuApi *api;
    u8 *display;
    if (state->debug >= 2) g_gpu_ot_status(g_str_display_enable_setdispmask_d_n,enabled);
    display = state->display;
    if (!enabled) memset(display,-1,20);
    api = g_gpu_ctl;
    command = 0x03000001;
    if (enabled) command = 0x03000000;
    api->ctl10(command);
}
