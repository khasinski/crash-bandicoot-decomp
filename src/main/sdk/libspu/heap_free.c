/* GCC_VERSION: 2.6.3 */
#include "common.h"


void _spu_gcSPU(void);


void SpuFree(u32 address)
{
    s32 i;

    for (i = 0; i < D_8005593C; i++) {
        if (g_spu_memList[i].address & 0x40000000) {
            break;
        }
        if (g_spu_memList[i].address == address) {
            g_spu_memList[i].address = address | 0x80000000;
            break;
        }
    }
    _spu_gcSPU();
}
