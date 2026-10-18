/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
/* GNU_AS_G: 8 */
#include "common.h"
void *LIBC_Malloc(s32);
extern void *D_800566B8;

extern s32 D_80056710;

typedef struct DrawBuffer {
    s16 unk0;
    s16 count;
} DrawBuffer;

s32 func_80029A58(void)
{
    s32 allocation_size;
    s32 capacity;
    DrawBuffer *first;
    DrawBuffer *second;

    if (D_80056710 == 0x19 || D_80056710 == 0x38) {
        capacity = 0xA32;
    } else {
        capacity = 0x5B4;
    }
    allocation_size = (capacity * 2) + 4;
    first = LIBC_Malloc(allocation_size);
    D_800566B8 = first;
    D_80056700 = first;
    if (first != NULL) {
        first->count = 0;
        second = LIBC_Malloc(allocation_size);
        D_800566BC = second;
        if (second != NULL) {
            second->count = 0;
            return -0xFF;
        }
    }
    return -0xF;
}
