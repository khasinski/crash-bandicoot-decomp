#include "common.h"
/* GCC_VERSION: 2.6.3 */


s32 _status(void) {
    return *g_gpu_stat_reg;
}
