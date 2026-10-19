#include "common.h"


void _SsTrapIntrVSync(void) {
    if (g_ss_vsync_prev_cb != 0) {
        g_ss_vsync_prev_cb();
    }
    g_ss_tick_cb();
}
