/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
extern u32 D_800549D0[];
u32 func_8003EF24(s32 index,u32 value) {
    u32 *table=D_800549D0;
    u32 *slot=table+index;
    u32 previous=*slot;
    if (value!=previous) *slot=value;
    return previous;
}
