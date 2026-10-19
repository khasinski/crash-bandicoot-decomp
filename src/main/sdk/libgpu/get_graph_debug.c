#include "common.h"
/* GCC_VERSION: 2.6.3 */

#define CRASH_EXT_SDK_LIBGPU_GET_GRAPH_DEBUG
#include "sdk_externs.h"
#undef CRASH_EXT_SDK_LIBGPU_GET_GRAPH_DEBUG

u8 GetGraphDebug(void) {
    return g_gpu_debug_level;
}
