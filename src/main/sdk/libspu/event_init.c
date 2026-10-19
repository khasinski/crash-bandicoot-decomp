#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Register the SPU callback and enable its event once. */

void EnterCriticalSection(void);
void _spu_FiDMA(void);
void _SpuCallback(void (*callback)(void));
s32 OpenEvent(u32,s32,s32,s32);
void EnableEvent(s32);
void ExitCriticalSection(void);
void SpuStart(void) {
    if (!g_spu_event_started) {
        g_spu_event_started = 1;
        EnterCriticalSection();
        g_spu_dma_started = 0;
        _SpuCallback(_spu_FiDMA);
        g_spu_dma_done_callback = OpenEvent(0xf0000009,32,0x2000,0);
        EnableEvent(g_spu_dma_done_callback);
        ExitCriticalSection();
    }
}
