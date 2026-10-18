/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "ns.h"
#include "zone.h"

ResourceSlot *func_800146F0(ResourceSlot *slot, s32 id, s32 entry_id, s32 *out, s32 flag);
void func_800134C8(s32 id);
ResourceSlot *func_80014C08(s32 id, s32 entry_id);

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

static __inline__ s32 func_80014E34(s32 id, s32 count)
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

static __inline__ ResourceSlot *func_80014F30(s32 addr)
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

s32 func_80015458(u32 *ref, s32 count)
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
    if (!(entry & 1)) {
        if (count == 0) {
        ret_1:
            return 1;
        }
        slot = func_80014F30(entry);
        if (slot == NULL) {
            goto ret_1;
        }
        return func_80014E34(slot->id, count);
    }
    if (count == 0) {
        return 0;
    }
    return func_80014E34(entry, count);
}

s32 func_800156D4(void)
{
    s32 free_count;
    s32 i;
    ResourceSlot *slot;

    free_count = D_8005C528.physical_count;
    for (i = 0; i < D_8005C528.pool.count; i++) {
        slot = &D_8005C528.pool.slots[i];
        if ((s16)slot->state != 1 && slot->references != 0) {
            free_count--;
        }
    }
    for (i = 0; i < D_8005C528.physical_count; i++) {
        slot = &D_8005C528.physical[i];
        if ((s16)slot->state != 1 && slot->references != 0) {
            free_count--;
        }
    }
    return free_count;
}

s32 func_8001579C(u32 **refs, s32 count)
{
    s32 seen_pages[40];
    s32 total = 0;
    s32 seen_count = 0;
    s32 i;
    s32 j;
    s32 id;
    ResourceBucket *bucket;
    s32 entry;
    ResourceSlot *phys_slot;
    ResourceSlot *page_slot;

    for (i = 0; i < count; i++) {
        id = *refs[i];
        if (id & 1) {
            bucket = func_80015978(id);
            *refs[i] = (u32)bucket;
        } else {
            bucket = (ResourceBucket *)id;
        }
        entry = bucket->entry;
        if (!(entry & 1)) {
            phys_slot = func_80014F30(entry);
            if (phys_slot != NULL) {
                if ((s16)phys_slot->state == 1 || phys_slot->references == 0) {
                    total++;
                }
            }
        } else {
            page_slot = D_8005C528.page_map[entry >> 1];
            if (page_slot == (ResourceSlot *)-0x12) {
                for (j = 0; j < seen_count; j++) {
                    if (entry == seen_pages[j]) {
                        break;
                    }
                }
                if (j == seen_count) {
                    total++;
                    seen_pages[seen_count++] = bucket->entry;
                }
            } else if (page_slot != (ResourceSlot *)-0xFF) {
                if (page_slot->references == 0) {
                    total++;
                }
            }
        }
    }
    return total;
}
