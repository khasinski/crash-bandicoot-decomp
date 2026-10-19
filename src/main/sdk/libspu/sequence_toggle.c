#include "common.h"


/* Call the registered callback on alternate invocations. */
void _SsSeqCalledTbyT_1per2(void) {
    if (g_spu_irq_installed == 0) {
        g_spu_irq_installed = 1;
        return;
    }
    g_spu_irq_installed = 0;
    g_ss_tick_cb();
}
