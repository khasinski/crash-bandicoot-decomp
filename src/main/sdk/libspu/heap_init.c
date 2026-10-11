/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

typedef struct { u32 address; s32 size; } HeapEntry;
extern s32 D_80055908;
extern s32 D_8005593C;
extern s32 D_80055940;
extern HeapEntry *D_80055944;

s32 func_80045D70(s32 capacity, HeapEntry *entries)
{
    s32 result = capacity;
    if (result > 0) {
        entries->address = 0x40001010;
        D_80055944 = entries;
        D_80055940 = 0;
        D_8005593C = result;
        entries->size = (s32)(((u32)0x10000 << D_80055908) - 0x1010);
    } else {
        return 0;
    }
    return result;
}
