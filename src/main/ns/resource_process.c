/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "gpu.h"
#include "ns.h"

typedef ResourceEntry Entry;
typedef ResourceHeader Header;
typedef ResourceSlot Slot;
extern Slot *D_8005CFAC;
typedef ResourceBucket Bucket;
typedef ResourceHandler Handler;
extern Slot D_8005C554[], D_800580A0[];
extern Handler D_800514EC[];
extern u32 D_8005728C[];
extern GpuRect D_80056420;
asm(".sdata\n.size D_80056420,8\n.text");

void func_80040484(GpuRect *, Header *);

u8 *func_80012F10(s32 index) {
    Slot *request = &D_8005C528.physical[index], *slot;
    Header *header;
    Bucket *bucket;
    s32 i, quotient;
    Entry *entry;
    s32 (*callback)(Entry *);

    if ((Slot *)D_8005C528.wordA84 == request)
        D_8005C528.wordA84 = 0;
    request->state = 30;
    header = request->header;
    switch (header->kind) {
    case 0:
        bucket = D_8005C528.buckets[(header->entries[0]->id >> 15) & 255];
        i = 0;
        while (i < request->header->count) {
            entry = request->header->entries[i];
            while (bucket->id != entry->id) {
                bucket++;
            }
            bucket->entry = (u32)entry;
            request->references++;
            callback = D_800514EC[entry->kind].callback;
            i++;
            if (callback)
                callback(entry);
            request->references--;
        }
        break;
    case 1: {
        Slot *texture_slot;
        i = func_8001439C();
        if (i == -12) {
            i = 15;
            if (request->references == 0)
                goto texture_done;
        }
        texture_slot = &D_800580A0[i];
        quotient = i / 4;
        D_80056420.x = (i - quotient * 4) << 8;
        D_80056420.y = quotient << 7;
        func_80040484(&D_80056420, request->header);
        texture_slot->state = 20;
        texture_slot->word18 = request->header->id;
        texture_slot->id = request->id;
        texture_slot->mapping = (u32 *)func_80015978(texture_slot->word18);
        *texture_slot->mapping = (u32)texture_slot->base;
    texture_done:
        request->state = 1;
        D_8005C528.page_map[request->id >> 1] = texture_slot;
        return (u8 *)(i * 2);
    }
    case 3:
    case 4:
        header = request->header;
        bucket = D_8005C528.buckets[(header->entries[0]->id >> 15) & 255];
        slot = request->slot;
        i = 0;
        while (i < header->count) {
            u8 *data;
            entry = header->entries[i];
            data = entry->data;
            while (bucket->id != entry->id) {
                bucket++;
            }
            if (i == 0) {
                if (request->header->kind == 4)
                    D_8005728C[slot->word08] = bucket->id;
                else
                    D_8005728C[slot->word08] = 0x6396347F;
            }
            bucket->entry = (u32)((((s32)data - (s32)request->header + (s32)slot->base) * 4) | 0x80000002);
            callback = D_800514EC[entry->kind].callback;
            i++;
            if (callback)
                callback(entry);
            header = request->header;
        }
        slot->state = 20;
        request->state = 1;
        D_8005C528.page_map[request->id >> 1] = slot;
        return slot->base;
    }
    request->state = 20;
    return (u8 *)request->header;
}

