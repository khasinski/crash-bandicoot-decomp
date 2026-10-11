#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Find an eight-byte entry in the ID hash bucket. */

typedef struct {
    s32 value;
    s32 id;
} ResourceEntry;
extern ResourceEntry **D_8005C530;
ResourceEntry *func_80015978(s32 id) {
    ResourceEntry *entry = D_8005C530[((u32)id >> 15) & 0xFF];
    while (entry->id != id) {
        entry++;
    }
    return entry;
}
