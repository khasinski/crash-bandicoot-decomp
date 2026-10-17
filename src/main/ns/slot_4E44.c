/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "ns.h"

extern ResourceHandler D_800514EC[];
extern s32 D_80056410;
extern volatile s32 D_80034520 __asm__("func_80034520");

s32 func_80013D48(ResourceSlot *slot, s32 arg1);
s32 func_800141F4(s32 *count_ptr, s32 arg1);
void *func_800146F0(ResourceSlot *slot, s32 id, s32 word18, s32 *count_ptr, s32 arg4);


ResourceSlot *func_80014644(s32 id, s32 word18)
{
    s32 i;
    ResourceSlot *slot;

    for (i = 0; i < D_8005C528.pool.count; i++) {
        slot = &D_8005C528.pool.slots[i];
        if ((s16)slot->state == 1) {
            slot->state = 2;
            slot->id = id;
            slot->references = 0;
            slot->word18 = word18;
            slot->word28 = D_80034520;
            D_8005C528.page_map[id >> 1] = slot;
            D_8005C528.pool.active_count++;
            return slot;
        }
    }
    return NULL;
}

void *func_800146F0(ResourceSlot *slot, s32 id, s32 word18, s32 *count_ptr, s32 arg4)
{
    s32 index;
    s32 count;
    ResourceSlot *phys;
    ResourceSlot *head;
    s32 i;
    s32 base_id;

    index = func_800141F4(count_ptr, arg4);
    if (index == -1) {
        return (void *)-12;
    }
    count = *count_ptr;
    phys = &D_8005C528.physical[index + count - 1];
    if (slot != NULL) {
        i = count - 1;
        base_id = slot->id;
        head = phys;
        if (i >= 0) {
            do {
                slot = D_8005C528.page_map[(base_id >> 1) + i];
                phys->id = slot->id;
                if (word18 != 0x6396347F) {
                    phys->word18 = word18;
                } else {
                    phys->word18 = slot->word18;
                }
                slot->state = 1;
                phys->references = slot->references;
                phys->word28 = slot->word28;
                phys->base = (u8 *)*count_ptr;
                phys->slot = head;
                if (i == *count_ptr - 1) {
                    phys->state = 2;
                } else {
                    phys->state = (count = 12);
                }
                D_8005C528.page_map[phys->id >> 1] = phys;
                phys--;
                i--;
            } while (i >= 0);
        }
        return head;
    }
    *count_ptr = 1;
    phys->id = id;
    phys->word18 = word18;
    phys->references = 0;
    phys->word28 = D_80034520;
    D_8005C528.pool.active_count++;
    phys->base = (u8 *)1;
    phys->slot = phys;
    phys->state = 2;
    D_8005C528.page_map[phys->id >> 1] = phys;
    return phys;
}
