/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "ns.h"
#include "zone.h"

extern ResourceSlot D_8005C554[] __asm__("D_8005C528 + 44");

ResourceSlot *func_800146F0(ResourceSlot *slot, s32 id, s32 entry_id, s32 *out, s32 flag);
void func_800134C8(s32 id);
ResourceSlot *func_80014C08(s32 id, s32 entry_id);
s32 func_80014E34(s32 id, s32 count);
ResourceSlot *func_80015034(u32 *ref);

static __inline__ void ns_slot_unref(ResourceSlot *slot)
{
    s16 references = slot->references;
    s16 remaining;

    if (references > 0) {
        remaining = references - 1;
        slot->references = remaining;
        if ((remaining << 16) <= 0 && slot->word06 == 0) {
            func_80014930(slot);
            D_8005C528.pool.active_count -= 1;
        }
    }
}

static __inline__ void ns_pool_active_inc(void)
{
    D_8005C528.pool.active_count++;
}


s32 func_80014E34(s32 id, s32 count)
{
    ResourceSlot *slot;
    s32 i;

    slot = D_8005C528.page_map[id >> 1];
    if ((s32)slot >= -0xFE) {
        return 0;
    }
    if (slot == (ResourceSlot *)-0xFF) {
        return 1;
    }
    if ((u16)slot->word06 >= 2 && (u16)slot->word06 <= 3) {
        return 1;
    }
    for (i = 0; i < count; i++) {
        ns_slot_unref(slot);
    }
    return slot->references + 1;
}

__inline__ ResourceSlot *func_80014F30(s32 addr)
{
    s32 i;
    ResourceSlot *slot;
    s32 header;

    if (addr & 2) {
        return NULL;
    }
    for (i = 0; i < D_8005C528.physical_count; i++) {
        slot = &D_8005C528.physical[i];
        header = (s32)slot->header;
        if (addr >= header && addr < header + 0x10000) {
            return slot;
        }
    }
    return NULL;
}

ResourceHeader *func_80014FA8(s32 addr)
{
    ResourceSlot *slot = func_80014F30(addr);

    if (slot != NULL) {
        return slot->header;
    }
    return NULL;
}

ResourceSlot *func_80015034(u32 *ref)
{
    s32 id;
    ResourceBucket *bucket;
    s32 entry;
    ResourceSlot *slot;

    id = *ref;
    if (id & 1) {
        bucket = func_80015978(id);
        *ref = (u32)bucket;
    } else {
        bucket = (ResourceBucket *)id;
    }
    entry = bucket->entry;
    if (entry & 1) {
        return D_8005C528.page_map[entry >> 1];
    }
    slot = func_80014F30(entry);
    if (slot != NULL) {
        return slot;
    }
    return (ResourceSlot *)-0xFF;
}

static __inline__ ResourceSlot *ns_find_physical(s32 addr)
{
    register ResourceSlot *slot;
    register s32 i;
    s32 header;

    if (!(addr & 2)) {
        for (i = 0; i < D_8005C528.physical_count; i++) {
            slot = &D_8005C554[i];
            header = (s32)slot->header;
            if (addr >= header && addr < header + 0x10000) {
                return slot;
            }
        }
    }
    return NULL;
}
