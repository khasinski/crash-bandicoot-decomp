#include "common.h"

/* GCC_VERSION: 2.6.3 */
/* CC1_FLAGS: -O1 */

/* Hash buckets point into eight-byte resource entries. */
typedef struct Entry {u32 word00,id;} Entry;
typedef struct {u8 pad[0x404];s32 count;} Metadata;
extern Entry **D_8005C530;
extern Entry *D_8005C534;
extern Metadata *D_8005C540;
Entry *func_800159C4(u32 id) {
    Entry *cursor = D_8005C530[(id >> 15) & 255];
    if (cursor->id == id) goto done;
    {
    Metadata *metadata = D_8005C540;
    Entry *base = D_8005C534;
    s32 count = metadata->count;
    cursor++;
search:
    if (((s32)((u8 *)cursor - (u8 *)base) >> 3) >= count) return (Entry *)-10;
    {
        u32 candidate = cursor->id;
        cursor++;
        if (candidate != id) goto search;
    }
    cursor--;
    }
done:
    return cursor;
}
