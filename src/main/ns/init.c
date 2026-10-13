/* GCC_VERSION: 2.6.3 */
#include "common.h"
#include "ns.h"

/* Use the CD (disc map) rather than host files. Only this unit addresses the
 * flag through $gp, so it owns the .sdata word. */
s32 D_80056410 = 1;

extern s32 D_80056710, D_80056714;
extern ResourceSlot D_80057F40[8];
extern u32 D_8005728C[8];
extern const char D_80010064[];     /* "Inited and Allocated %d pages\n" */

s32 func_800128A4(s32, s32, s32, s32);
char *BIOS_StrCpy(char *, const char *);
void *LIBC_Malloc(s32);
void *LIBC_Realloc(void *, s32);
u8 *func_80043A24(s32, u8 *);
s32 func_80043520(u8, u8 *, u8 *);
s32 func_800439A4(s32, void *, s32);
s32 func_80043984(s32, s32);
void func_800322CC(s32, void *, void *);
s32 func_8003D730(const char *, ...);
s32 func_800126C0(ResourceBucket *);

/* The entry search of func_800159C4, expanded inline at both uses. */
static __inline__ ResourceBucket *ns_lookup(u32 id)
{
    ResourceBucket *cursor = D_8005C528.buckets[(id >> 15) & 255];

    while (cursor->id != id) {
        cursor++;
        if (((s32)((u8 *)cursor - (u8 *)D_8005C528.entries) >> 3)
            >= D_8005C528.directory->entry_count) {
            return (ResourceBucket *)-10;
        }
    }
    return cursor;
}

/* Read a level's directory file through the disc map, in whole sectors. */
static __inline__ NsDirectory *ns_read_directory(s32 level)
{
    u8 result[8];
    u8 position[4];
    NsFileMap *map;
    NsDirectory *buffer;

    map = &D_8005E03C[level];
    buffer = LIBC_Malloc(((map->directory_size & 0x1FFFF) + 0x7FF) / 0x800 * 0x800);
    if (buffer == NULL) {
        return (NsDirectory *)-15;
    }
    func_80043A24(map->directory_sector & 0x7FFFFF, position);
    func_80043520(2, position, result);
    if (!func_800439A4(((map->directory_size & 0x1FFFF) + 0x7FF) / 0x800, buffer, 0x80)
        || func_80043984(0, 0)) {
        return (NsDirectory *)-16;
    }
    return LIBC_Realloc(buffer, map->directory_size & 0x1FFFF);
}

/* Start paging for a level: read its directory, size the page map, allocate
 * physical pages and assign the VRAM texture pages and SPU audio pages. */
s32 func_80015B58(NsState *ns, s32 level)
{
    char filename[0x100];
    NsDirectory *directory;
    ResourceSlot *slot;
    ResourceBucket *entry;
    s32 i, j, column, row, page, clut, word, type;

    if (ns->initialized != 0) {
        return -0xFF;
    }
    D_80056714 = -1;
    D_80056710 = level;
    ns->initialized = 1;
    ns->wordA84 = 0;
    ns->pool.active_count = 0;
    ns->wordA8C = 0;
    ns->level = level;
    ns->wordA90 = 0;
    ns->wordA98 = 1;
    BIOS_StrCpy(filename, (char *)func_800128A4(0, level, 0, 0));

    /* Without the CD the host-file read is compiled out; retail stores the
     * uninitialized local. */
    if (D_80056410) {
        ns->directory = ns_read_directory(level);
    } else {
        ns->directory = directory;
    }

    ns->level_eid = &ns->directory->level_eid;
    ns->buckets = (ResourceBucket **)ns->directory;
    ns->entries = ns->directory->entries;
    ns->level_header = (u8 *)&ns->directory->entries[ns->directory->entry_count];
    func_800322CC(level, ns->directory->entry_count * 8 + 0x730 + (u8 *)ns->directory, ns->directory);
    /* Drop the loading-screen image that follows the level header. */
    ns->directory = LIBC_Realloc(ns->directory, ns->directory->entry_count * 8 + 0x730);
    for (i = 0; i < 0x100; i++) {
        ns->buckets[i] = &ns->entries[((s32 *)ns->buckets)[i]];
    }

    BIOS_StrCpy(filename, (char *)func_800128A4(1, level, 0, 0));
    if (D_80056410) {
        D_8005C528.nsf_sector = D_8005E03C[level].page_sector & 0xFFFFFF;
    }
    ns->page_map = LIBC_Malloc(ns->directory->page_count * 4);
    for (i = 0; i < ns->directory->page_count; i++) {
        ns->page_map[i] = (ResourceSlot *)-18;
    }
    for (i = 0; i < 21; i++) {
        if (D_800514E0[i].init) {
            D_800514E0[i].init();
        }
    }

    /* Up to 22 physical 64 KB pages, fewer if memory is short. */
    ns->physical_count = 22;
    i = 22;
    do {
        if ((ns->physical[0].header = LIBC_Malloc(i << 16)) != NULL) {
            break;
        }
    } while (--i >= 0);
    ns->physical_count = i;
    for (i = 0; i < ns->physical_count; i++) {
        ns->physical[i].state = 1;
        ns->physical[i].word06 = 1;
        ns->physical[i].header = (ResourceHeader *)((u8 *)ns->physical[0].header + (i << 16));
        ns->physical[i].word08 = i;
        ns->physical[i].references = 0;
    }
    ns->pool.count = 38;
    for (i = 0; i < ns->pool.count; i++) {
        ns->pool.slots[i].state = 1;
        ns->pool.slots[i].word06 = 0;
        ns->pool.slots[i].header = NULL;
        ns->pool.slots[i].references = 0;
    }
    func_8003D730(D_80010064, ns->physical_count);

    /* Texture pages: VRAM as a 4x4 grid of 256x128 blocks. Pages 0-3 hold the
     * display buffer and 4-7 the draw buffer; a page still loaded from the
     * previous level is kept if its entry exists in this level too. */
    for (i = 0; i < 16; i++) {
        D_800580A0[i].word06 = 2;
        column = i % 4;
        row = i / 4;
        page = column << 2;
        if (i >= 8) {
            page |= 0x10;
        }
        clut = (column << 8) | (row << 17);
        if (row & 1) {
            word = clut | 0x80;
            D_800580A0[i].base = (u8 *)(0x80000002 | (page | word));
        } else {
            D_800580A0[i].base = (u8 *)(0x80000002 | (page | clut));
        }
        if ((i >= 0 && i < 4) || (i >= 4 && i < 8)) {
            D_800580A0[i].state = 30;
        } else {
            slot = &D_800580A0[i];
            if (slot->state == 20 || slot->state == 21) {
                entry = ns_lookup(D_800580A0[i].word18);
                if ((s32)entry < -0xFE) {
                    D_800580A0[i].state = 20;
                    D_800580A0[i].id = entry->entry;
                    D_800580A0[i].mapping = (u32 *)entry;
                    D_8005C528.page_map[D_800580A0[i].id >> 1] = &D_800580A0[i];
                    entry->entry = (u32)D_800580A0[i].base;
                } else {
                    D_800580A0[i].state = 21;
                }
            } else {
                D_800580A0[i].state = 1;
            }
        }
    }

    /* Audio pages: eight SPU pages, minus one per wavebank entry (type 14) in
     * the level. The level number is no longer needed and counts them. */
    type = 14;
    level = 0;
    for (j = 0; j < ns->directory->entry_count; j++) {
        if (func_800126C0(&ns->directory->entries[j]) == type) {
            level++;
        }
    }
    D_8005C528.audio_page_count = 8 - level;
    if (D_8005C528.audio_page_count < 2) {
        D_8005C528.audio_page_count = 2;
    }
    switch (D_80056710) {
    case 3: case 0x22: case 0x29: case 0x2B: case 0x2E: case 0x38:
        break;
    default:
        if (D_8005C528.audio_page_count >= 5) {
            D_8005C528.audio_page_count = 4;
        }
        break;
    }
    for (i = 0; i < 8; i++) {
        D_80057F40[i].word08 = i;
        if (i < D_8005C528.audio_page_count) {
            D_80057F40[i].state = 1;
            D_80057F40[i].word06 = 3;
            D_80057F40[i].base = (u8 *)(0x2000 + (i << 16));
        } else {
            D_80057F40[i].state = 1;
            D_80057F40[i].word06 = 4;
            D_80057F40[i].base = (u8 *)(0x2000 + (D_8005C528.audio_page_count << 16)
                                        + 0xFF90 * (i - D_8005C528.audio_page_count));
        }
    }
    /* Keep instrument pages whose entries are still present. */
    for (i = 0; i < 8; i++) {
        if (D_8005728C[i] != 0x6396347F && D_80057F40[i].word06 == 4) {
            entry = ns_lookup(D_8005728C[i]);
            if ((s32)entry >= -0xFE) {
                D_8005728C[i] = 0x6396347F;
            } else {
                D_8005C528.page_map[(s32)entry->entry >> 1] = &D_80057F40[i];
                D_80057F40[i].state = 20;
                D_80057F40[i].id = entry->entry;
                D_80057F40[i].word18 = D_8005728C[i];
                entry->entry = 0x80000002;
            }
        }
    }

    for (i = 0; i < 21; i++) {
        if (D_800514E0[i].init_pages) {
            D_800514E0[i].init_pages();
        }
    }
    return -0xFF;
}

INCLUDE_ASM("asm/USA/main/nonmatchings/ns/init", func_80016420);
