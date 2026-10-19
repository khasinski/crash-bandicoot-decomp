#include "resource.h"

/* GCC_VERSION: 2.6.3 */

/* The second resource pool has 38 slots, each 0x2C bytes long. */

void Ns_PageDecRef(ResourceSlot *slot)
{
    s16 references = slot->references;
    s16 remaining;

    if (references > 0) {
        remaining = references - 1;
        slot->references = remaining;
        if ((remaining << 16) <= 0 && slot->word06 == 0) {
            Ns_PageDelete(slot);
            D_8005C91C.active_count -= 1;
        }
    }
}
