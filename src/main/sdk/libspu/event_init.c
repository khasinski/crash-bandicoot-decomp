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
    if (!D_80055DA8) {
        D_80055DA8 = 1;
        EnterCriticalSection();
        D_80055948 = 0;
        _SpuCallback(_spu_FiDMA);
        D_800559A0 = OpenEvent(0xf0000009,32,0x2000,0);
        EnableEvent(D_800559A0);
        ExitCriticalSection();
    }
}
