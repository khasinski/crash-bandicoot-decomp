#ifndef CRASH_RESOURCE_H
#define CRASH_RESOURCE_H

#include "common.h"

/* Eight-byte handles cache a tagged entry word and its resource identifier. */
typedef struct ResourceHandle {
    u32 entry;
    u32 id;
} ResourceHandle;

typedef struct ResourceEntry {
    u32 word00;
    u32 id;
    s32 kind;
    s32 word0C;
    u8 *data;
} ResourceEntry;

typedef struct ResourceHeader {
    u16 word00;
    u16 kind;
    u32 id;
    u32 count;
    u32 word0C;
    ResourceEntry *entries[1];
} ResourceHeader;

/* The resource arrays advance by 0x2C bytes. Offsets and signedness are
 * recovered from processing, releasing and decrementing slot references.
 * Fields whose purpose remains unknown retain their offset names.
 */
typedef struct ResourceSlot {
    ResourceHeader *header;
    u16 state;
    s16 word06;
    s16 word08;
    s16 references;
    u32 word0C;
    u32 word10;
    s32 id;
    s32 word18;
    u8 *base;
    u32 *mapping;
    struct ResourceSlot *slot;
    u32 word28;
} ResourceSlot;

#endif
