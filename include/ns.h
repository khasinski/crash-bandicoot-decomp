#ifndef CRASH_NS_H
#define CRASH_NS_H

#include "common.h"
#include "resource.h"

/* Directory (NSD) file read at level start: 256 bucket offsets, page and
 * entry counts, the level ID word, then the entry table followed by the
 * level header. The bucket offsets are rewritten in place into pointers. */
typedef struct NsDirectory {
    s32 bucket_offsets[0x100];
    s32 page_count;
    s32 entry_count;
    u32 level_eid;
    s32 word40C;
    s32 word410;
    s32 word414;
    u8 pad418[0x520 - 0x418];
    ResourceBucket entries[1];
} NsDirectory;

/* Paging state at D_8005C528. The 22 physical page slots, the 38-slot pool
 * of virtual pages and the page map are set up by func_80015B58. */
typedef struct NsState {
    s32 initialized;
    s32 level;
    ResourceBucket **buckets;
    ResourceBucket *entries;
    u32 *level_eid;
    u8 *level_header;
    NsDirectory *directory;
    u8 pad1C[4];
    u32 nsf_sector;
    s32 draw_skip;
    s32 physical_count;
    ResourceSlot physical[22];
    ResourcePool pool;
    s32 wordA84;
    s32 audio_page_count;
    s32 wordA8C;
    s32 wordA90;
    ResourceSlot **page_map;
    s32 wordA98;
} NsState;

/* Twelve-byte disc map records indexed by level: directory sector and size,
 * then the sector of the level's page (NSF) file. */
typedef struct NsFileMap {
    s32 directory_sector;
    s32 directory_size;
    s32 page_sector;
} NsFileMap;

/* 21 records at D_800514E0; +4 runs before the pages are set up, +8 after. */
typedef struct NsSubsystem {
    u32 word00;
    void (*init)(void);
    void (*init_pages)(void);
    u8 pad0C[8];
    void (*kill)(void);
    u32 word18;
} NsSubsystem;

extern NsState D_8005C528;
extern ResourceSlot D_8005C920[];
extern NsFileMap D_8005E03C[];
extern NsSubsystem D_800514E0[];

s32 func_80015B58(NsState *ns, s32 level);
s32 func_80016420(NsState *ns);

#endif
