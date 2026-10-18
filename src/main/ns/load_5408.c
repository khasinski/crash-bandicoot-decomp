/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "ns.h"
#include "zone.h"

extern const u32 D_80034520 __asm__("func_80034520");

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


#define NS_FIND_OR_ALLOC_SLOT(res_slot, page_id, ent_id, found_label, search_label, done_label) \
    do { \
        ResourceSlot *_cand; \
        s32 _i; \
        u32 _ticks; \
        (res_slot) = D_8005C528.page_map[(page_id) >> 1]; \
        if ((res_slot) == (ResourceSlot *)-0x12) { \
            goto search_label; \
        } \
        if ((res_slot) != (ResourceSlot *)-0xFF) { \
            (res_slot)->word18 = (ent_id); \
        } \
        goto done_label; \
    found_label: \
        _ticks = D_80034520; \
        _cand->state = 2; \
        _cand->id = (page_id); \
        _cand->references = 0; \
        _cand->word18 = (ent_id); \
        _cand->word28 = _ticks; \
        D_8005C528.page_map[(page_id) >> 1] = _cand; \
        ns_pool_active_inc(); \
        (res_slot) = _cand; \
        goto done_label; \
    search_label: \
        for (_i = 0; _i < D_8005C91C.count; _i++) { \
            _cand = &D_8005C920[_i]; \
            if ((s16)_cand->state == 1) { \
                goto found_label; \
            } \
        } \
        (res_slot) = NULL; \
    done_label:; \
    } while (0)


ResourceSlot *func_80014C08(s32 id, s32 entry_id)
{
    ResourceSlot *slot;
    s32 sp18;
    s32 sp1C;

    slot = D_8005C528.page_map[id >> 1];
    if ((s32)slot >= -0xFE) {
        sp18 = 1;
        slot = func_800146F0(NULL, id, entry_id, &sp18, 1);
        if ((s32)slot < -0xFE) {
            goto sync_page;
        }
        return slot;
    }
    if (slot == (ResourceSlot *)-0xFF || ((u16)slot->word06 >= 2 && (u16)slot->word06 <= 3)) {
        return slot;
    }
    if (slot->word06 == 0) {
        sp1C = 1;
        slot = func_800146F0(slot, id, entry_id, &sp1C, 1);
        if ((s32)slot < -0xFE) {
            goto sync_page;
        }
        return slot;
    }
    slot->word18 = entry_id;
    if ((s16)slot->state != 0x14) {
    sync_page:
        func_800134C8(id);
        slot = D_8005C528.page_map[id >> 1];
    }
    return slot;
}
