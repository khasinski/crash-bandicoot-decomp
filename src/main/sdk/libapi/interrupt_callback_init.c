#include "common.h"

/* GCC_VERSION: 2.6.3 */
typedef void (*Callback)(void);
typedef Callback (*Registrar)(s32,Callback);
Callback InterruptCallback(s32,Callback);
void trapIntrVSync(void),trapIntrDMA(void);
Callback setIntrVSync(s32,Callback),setIntrDMA(s32,Callback);
void rcnt_memclr(Callback *,s32),dma_memclr(Callback *,s32);
Registrar startIntrDMA(void) {
    dma_memclr(g_dma_cb_slots, 8);
    *g_dma_dicr_reg = 0;
    InterruptCallback(3, &trapIntrDMA);
    return &setIntrDMA;
}
