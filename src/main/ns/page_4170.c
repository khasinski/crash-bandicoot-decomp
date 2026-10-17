/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"
#include "ns.h"
#include "zone.h"

extern s32 D_80056410;
extern ResourceSlot D_80057F40[8];

s32 func_80043984(s32, s32);
s32 func_80043498(s32, s32);
u8 *func_80043A24(s32, u8 *);
s32 func_80043668(u8, u8 *);
s32 func_800439A4(s32, void *, s32);
void func_80012F10(s32);
void func_80048A18(u32);
void func_800489B8(void *, s32);
s32 func_80048A88(s32);
void func_8001331C(ResourceSlot *);

typedef struct NsDirectoryExt {
    s32 bucket_offsets[0x100];
    s32 page_count;
    s32 entry_count;
    u32 level_eid;
    s32 word40C;
    s32 word410;
    s32 word414;
    s32 word418;
    s32 word41C;
    u32 words420[1];
} NsDirectoryExt;

typedef struct PageSlot {
    u8 *header;
    u16 state;
    s16 word06;
    s16 word08;
    s16 references;
    s16 word0C;
    s16 word0E;
    u32 word10;
    s32 id;
    s32 word18;
    s32 word1C;
    s32 word20;
    struct PageSlot *slot;
    u32 word28;
} PageSlot;

void func_80013970(u8 *src, u8 *dst)
{
    u32 b0, b1, b2, b3;
    u32 b4, b5, b6, b7;
    u32 b8, b9, b10, b11;
    u32 magic;
    s32 comp_len;
    s32 skip_len;
    s32 rem;
    s32 len;
    u8 *back;

    b0 = src[0];
    b1 = src[1];
    b2 = src[2];
    b3 = src[3];
    src += 4;
    b4 = src[0];
    b5 = src[1];
    b6 = src[2];
    b7 = src[3];
    src += 4;
    b8 = src[0];
    b9 = src[1];
    b10 = src[2];
    b11 = src[3];
    src += 4;

    comp_len = b4 + (b5 << 8) + (b6 << 16) + (b7 << 24);
    magic = b0 + (b1 << 8) + (b2 << 16) + (b3 << 24);
    skip_len = b8 + (b9 << 8) + (b10 << 16) + (b11 << 24);

    if ((magic & 0xFFFF) == 0x1234) {
        if (src != dst) {
            src -= 12;
            for (len = 0; len <= 0xFFFF; len++) {
                *dst++ = *src++;
            }
        }
        return;
    }

    rem = 0x10000 - comp_len;
    if (comp_len != 0) {
        do {
            len = *src++;
            if (len & 0x80) {
                len = (len << 8) + *src++;
                back = dst - ((len >> 3) & 0xFFF);
                len &= 7;
                if (len == 7) {
                    len = 0x40;
                } else {
                    len += 3;
                }
                comp_len -= len;
                while (--len != -1) {
                    *dst++ = *back++;
                }
            } else {
                comp_len -= len;
                while (--len != -1) {
                    *dst++ = *src++;
                }
            }
        } while (comp_len != 0);
    }
    src += skip_len;
    while (--rem != -1) {
        *dst++ = *src++;
    }
}

static __inline__ s32 ns_page_resolve(ResourceHeader *page)
{
    s32 count = page->count;
    ResourceEntry **entries = page->entries;
    s32 i, j;
    ResourceEntry *entry;
    u32 *items;

    if (page->kind == 1) {
        return -0xFF;
    }
    if (page->word00 != 0x1234) {
        return -0x12;
    }
    for (i = count - 1; i >= 0; i--) {
        entry = (ResourceEntry *)((u8 *)page + (u32)entries[i]);
        entries[i] = entry;
        items = (u32 *)&entry->data;
        for (j = entry->word0C; j >= 0; j--) {
            items[j] = (u32)entry + items[j];
        }
    }
    entries[count] = (ResourceEntry *)((u8 *)page + (u32)entries[count]);
    return -0xFF;
}

static __inline__ s32 ns_cd_check(s32 enabled)
{
    s32 result = func_80043984(enabled == 0, 0);
    if (result < 0)
        return 0;
    return result == 0;
}

static __inline__ s32 ns_cd_read(PageSlot *slot, s32 count)
{
    u8 loc[16];
    s32 id;
    s32 sectors;
    u8 *buf;
    s32 pos;

    id = slot->id;
    if (slot->word0E != 0) {
        sectors = (count << 5) - slot->word0C;
        buf = slot->header + (slot->word0C << 11);
        pos = D_8005C528.nsf_sector + (((NsDirectoryExt *)D_8005C528.directory)->words420[id >> 1] >> 6);
    } else {
        sectors = count << 5;
        pos = D_8005C528.nsf_sector + ((NsDirectoryExt *)D_8005C528.directory)->word418 + ((id >> 1) << 5);
        buf = slot->header;
    }
    func_80043A24(pos, loc);
    func_80043668(2, loc);
    if (func_800439A4(sectors, buf, 0x80) == 0) {
        return -0x10;
    }
    return -0xFF;
}

PageSlot *NS_13B30(PageSlot *slot)
{
    s32 state = (s16)slot->state;
    s32 count = slot->word1C;
    s32 offset = 0;
    s32 compressed;
    s32 i;
    s32 next_offset;
    PageSlot *prev;

    if (state == 3 || state == 0xD) {
        if (slot->word0E != 0) {
            func_80013970(slot->header + (slot->word0C << 11), slot->header);
        }
        slot->state = 4;
        ns_page_resolve((ResourceHeader *)slot->header);
        return NULL;
    }

    compressed = (slot->id >> 1) < ((NsDirectoryExt *)D_8005C528.directory)->word41C && D_8005C528.wordA98 != 0;
    for (i = 0; i < count; i++) {
        if (state == 2) {
            slot->word0E = compressed;
            if (compressed != 0) {
                next_offset = offset + 0x20;
                offset = next_offset - (((NsDirectoryExt *)D_8005C528.directory)->words420[slot->id >> 1] & 0x3F);
                slot->word0C = offset;
            }
            if ((s16)slot->state == state) {
                slot->state = 3;
            } else {
                slot->state = 0xD;
                if (compressed != 0) {
                    slot->word10 = (u32)(slot->header + (((((NsDirectoryExt *)D_8005C528.directory)->words420[slot->id >> 1] & 0x3F) + slot->word0C) << 11));
                } else {
                    slot->word10 = (u32)slot[1].header;
                }
                *(u16 *)slot->word10 = 0x8765;
            }
        }
        prev = slot;
        slot--;
    }
    return prev;
}

void func_80013D48(PageSlot *slot, s32 id)
{
    PageSlot *next_slot;
    s32 shifted_id;
    s32 max;
    s32 in_range;
    s32 arg1;
    u16 kind;
    s32 idx;
    ResourceSlot *spu_slot;
    ResourceHeader *header;
    ResourceEntry *entry;

loop:
    switch ((s16)slot->state) {
    case 13:
        if (id == -1) {
            if (*(u16 *)slot->word10 == 0x8765) {
                break;
            }
        } else if (!ns_cd_check(1)) {
            break;
        }
        NS_13B30(slot);
        if (id != -1 && slot != slot->slot) {
            func_80013D48(slot + 1, id);
        }
        goto case_4;
    case 2:
        if (D_8005C528.wordA84 != 0) {
            break;
        }
        if (id != -1) {
            shifted_id = id >> 1;
            max = slot->slot->id >> 1;
            in_range = shifted_id <= max && shifted_id > max - slot->word1C;
            if (!in_range) {
                break;
            }
        }
        D_8005C528.wordA90 = slot->id;
        if (D_80056410 == 0) {
            goto abort_cd;
        }
        if (func_80043498(1, 0) != 2 && id == -1) {
            break;
        }
        next_slot = NS_13B30(slot);
        D_8005C528.wordA84 = (s32)slot;
        ns_cd_read(next_slot, slot->word1C);
        slot = next_slot;
        goto loop;
    case 3:
        if (D_80056410 != 0 && (PageSlot *)D_8005C528.wordA84 == slot) {
            if (id == -1) {
                if (ns_cd_check(0)) {
                    goto finish_cd;
                }
                if (id == -1) {
                    break;
                }
            }
            if (!ns_cd_check(1)) {
                break;
            }
        finish_cd:
            NS_13B30(slot);
            D_8005C528.wordA84 = 0;
        } else {
        abort_cd:
            func_80014930((ResourceSlot *)slot);
            D_8005C528.wordA84 = 0;
            D_8005C528.pool.active_count--;
            break;
        }
    case 4:
    case_4:
        if ((u16)(((ResourceHeader *)slot->header)->kind - 3) >= 2) {
            func_80012F10(slot->word08);
            D_8005C528.pool.active_count--;
            break;
        }
        slot->state = 10;
    case 10:
        if (D_8005C528.wordA8C != 0) {
            break;
        }
        if (id != -1 && id != slot->id) {
            break;
        }
        arg1 = -1;
        kind = ((ResourceHeader *)slot->header)->kind;
        if (kind == 4) {
            arg1 = *(s32 *)(((ResourceHeader *)slot->header)->entries[0]->data) + D_8005C528.audio_page_count;
        }
        idx = func_800145C8(kind, arg1);
        if (idx == -12) {
            func_80014930((ResourceSlot *)slot);
            D_8005C528.pool.active_count--;
            break;
        }
        spu_slot = &D_80057F40[idx];
        slot->state = 11;
        slot->slot = (PageSlot *)spu_slot;
        D_8005C528.wordA8C = (s32)slot;
        spu_slot->state = 11;
        spu_slot->id = slot->id;
        func_80048A18((u32)spu_slot->base);
        header = (ResourceHeader *)slot->header;
        if (header->kind == 3) {
            func_800489B8(header, 0x10000);
        } else if (header->kind == 4) {
            entry = header->entries[0];
            func_800489B8((&entry->data)[1], ((s32 *)entry->data)[1]);
        }
    case 11:
        if ((PageSlot *)D_8005C528.wordA8C == slot) {
            if (func_80048A88(id == slot->id)) {
                func_80012F10(slot->word08);
                D_8005C528.wordA8C = 0;
                D_8005C528.pool.active_count--;
            }
        }
        break;
    case 31:
        slot->state = 1;
        break;
    }
}

s32 func_800141F4(s32 *count)
{
    s32 best_start = -1;
    s32 best_len;
    u32 best_cost;
    s32 i;
    s32 j;
    u32 cost;
    ResourceSlot *slot;
    ResourceSlot *phys;
    s16 state;

    for (i = 0; i < D_8005C528.physical_count; i++) {
        phys = D_8005C528.physical;
        cost = 0;
        for (j = 0; j < (*count < D_8005C528.physical_count - i ? *count : D_8005C528.physical_count - i); j++) {
            slot = (ResourceSlot *)((i + j) * sizeof(ResourceSlot) + (s32)phys);
            state = slot->state;
            if (state != 1) {
                if ((u16)(state - 20) >= 2) {
                    break;
                }
                if (slot->references > 0) {
                    break;
                }
                cost += slot->word28 + 1;
            }
            if (best_start == -1 || best_len < j + 1 || (best_len == j + 1 && cost < best_cost)) {
                best_start = i;
                best_len = j + 1;
                best_cost = cost;
            }
        }
    }
    if (best_start != -1) {
        for (j = best_start; j < best_start + best_len; j++) {
            func_8001331C(&D_8005C528.physical[j]);
        }
        *count = best_len;
        return best_start;
    }
    *count = 0;
    return -1;
}
