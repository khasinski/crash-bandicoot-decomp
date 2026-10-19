#include "common.h"

/* GCC_VERSION: 2.6.3 */
typedef void (*Callback)(void);
typedef Callback (*Registrar)(s32,Callback);
Callback InterruptCallback(s32,Callback);
void trapIntrVSync(void),trapIntrDMA(void);
Callback setIntrVSync(s32,Callback),setIntrDMA(s32,Callback);
void rcnt_memclr(Callback *,s32),dma_memclr(Callback *,s32);
Registrar startIntrVSync(void) {
    *g_vsync_rcnt1_mode_reg = 0x107;
    g_vsync_cb_active_cnt = 0;
    rcnt_memclr(g_vsync_cb_slots, 8);
    InterruptCallback(0, &trapIntrVSync);
    return &setIntrVSync;
}
