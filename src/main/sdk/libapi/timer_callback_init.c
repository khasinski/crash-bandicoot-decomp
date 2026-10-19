#include "common.h"

/* GCC_VERSION: 2.6.3 */
typedef void (*Callback)(void);
typedef Callback (*Registrar)(s32,Callback);
Callback InterruptCallback(s32,Callback);
void trapIntrVSync(void),trapIntrDMA(void);
Callback setIntrVSync(s32,Callback),setIntrDMA(s32,Callback);
void rcnt_memclr(Callback *,s32),dma_memclr(Callback *,s32);
Registrar startIntrVSync(void) {
    *D_800549F4 = 0x107;
    D_800549F0 = 0;
    rcnt_memclr(D_800549D0, 8);
    InterruptCallback(0, &trapIntrVSync);
    return &setIntrVSync;
}
