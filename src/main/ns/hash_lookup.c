#include "resource.h"

/* GCC_VERSION: 2.6.3 */

/* Find an eight-byte entry in the ID hash bucket. */

ResourceBucket *Ns_Probe(s32 id) {
    ResourceBucket *entry = D_8005C530[((u32)id >> 15) & 0xFF];
    while (entry->id != id) {
        entry++;
    }
    return entry;
}
