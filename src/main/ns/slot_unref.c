#include "resource.h"

/* GCC_VERSION: 2.6.3 */

/* The second resource pool has 38 slots, each 0x2C bytes long. */
typedef struct ResourcePool {
    s32 count;
    u8 slots[38][0x2C];
    s32 active_count;
} ResourcePool;

extern ResourcePool D_8005C91C;
void func_80014930(ResourceSlot *slot);

void func_800148C4(ResourceSlot *slot)
{
    s16 references = slot->references;
    s16 remaining;

    if (references > 0) {
        remaining = references - 1;
        slot->references = remaining;
        if ((remaining << 16) <= 0 && slot->word06 == 0) {
            func_80014930(slot);
            D_8005C91C.active_count -= 1;
        }
    }
}
