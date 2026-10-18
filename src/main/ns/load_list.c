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


void func_8001495C(ZoneLoadList *load)
{
    s32 i;
    ResourceSlot *slot;

    if (load != NULL) {
        for (i = 0; i < load->entry_count; i++) {
            slot = func_80015034(&load->entries[i]);
            if ((s32)slot < -0xFE && slot != (ResourceSlot *)-0xFF) {
                ns_slot_unref(slot);
            }
        }
        for (i = 0; i < load->page_count; i++) {
            func_80014E34(load->pages[i], 1);
        }
    }
}
