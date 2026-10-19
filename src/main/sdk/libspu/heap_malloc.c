/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"





void _spu_gcSPU(void);

s32 SpuMalloc(s32 size) {
    s32 i = 0;
    s32 found = -1;
    s32 rev_size;
    s32 temp;
    u32 temp_addr;
    u32 temp_size;
    u32 block_size;

    if (D_80055954 == 0) {
        rev_size = 0;
    } else {
        rev_size = (0x10000 - D_80055958) << g_spu_trans_mode;
    }
    if (size & ~D_80055910) {
        temp = size + D_80055910;
    } else {
        temp = size;
    }
    size = temp >> g_spu_trans_mode;
    size = size << g_spu_trans_mode;
    if (g_spu_memList->address & 0x40000000) {
        found = 0;
    } else {
        _spu_gcSPU();
        for (; i < D_8005593C; i++) {
            if ((g_spu_memList[i].address & 0x40000000) ||
                ((g_spu_memList[i].address & 0x80000000) && (g_spu_memList[i].size >= (u32)size))) {
                found = i;
                break;
            }
        }
    }
    if (found == -1) {
        return -1;
    }
    if (g_spu_memList[found].address & 0x40000000) {
        if ((found < D_8005593C) && ((g_spu_memList[found].size - rev_size) >= (u32)size)) {
            g_spu_alloc_num = found + 1;
            g_spu_memList[g_spu_alloc_num].address = ((g_spu_memList[found].address & 0x0FFFFFFF) + size) | 0x40000000;
            g_spu_memList[g_spu_alloc_num].size = g_spu_memList[found].size - size;
            g_spu_memList[found].size = size;
            g_spu_memList[found].address &= 0x0FFFFFFF;
            _spu_gcSPU();
            return g_spu_memList[found].address;
        }
        return -1;
    }
    block_size = g_spu_memList[found].size;
    if ((u32)size < block_size) {
        if (g_spu_alloc_num < D_8005593C) {
            u32 new_addr = g_spu_memList[found].address + size;
            temp_addr = g_spu_memList[g_spu_alloc_num].address;
            temp_size = g_spu_memList[g_spu_alloc_num].size;
            g_spu_memList[g_spu_alloc_num].address = new_addr | 0x80000000;
            g_spu_memList[g_spu_alloc_num].size = block_size - size;
            g_spu_memList[g_spu_alloc_num + 1].address = temp_addr;
            g_spu_memList[g_spu_alloc_num + 1].size = temp_size;
            g_spu_alloc_num++;
        }
    }
    g_spu_memList[found].size = size;
    g_spu_memList[found].address &= 0x0FFFFFFF;
    _spu_gcSPU();
    return g_spu_memList[found].address;
}
