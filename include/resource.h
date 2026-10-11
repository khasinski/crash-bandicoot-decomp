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

/* Item-pointer view used by func_80031D50 on a resolved resource entry.
 * The first item is at +0x10; subsequent items follow at four-byte intervals.
 * Keep separate from ResourceHeader, whose page-header fields differ. */
typedef struct ResourceItemListView {
    u8 pad00[0x10];
    u8 *items[1];
} ResourceItemListView;

/* The first item's word at +0x204 selects another item in that list.
 * The remainder of this item's layout and its complete size are unknown. */
typedef struct ResourceItemSelection {
    u8 pad00[0x204];
    u32 word204;
} ResourceItemSelection;

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

/* Hash lookup advances by eight bytes, not sizeof(ResourceEntry).
 * entry may contain a tagged/encoded address, so retain an integer word. */
typedef ResourceHandle ResourceBucket;

typedef struct ResourceHashMetadata {
    u8 pad00[0x404];
    s32 count;
} ResourceHashMetadata;

typedef struct ResourcePool {
    s32 count;
    ResourceSlot slots[38];
    s32 active_count;
} ResourcePool;

/* View based at slot + 4, used by the D_800580A4 alias in func_80014514.
 * The array still advances by 0x2C. Do not confuse this base with a full slot. */
typedef struct ResourceSlotStateView {
    s16 state;
    u8 pad02[0xE];
    s32 id;
    u8 pad14[8];
    s32 *id_pointer;
    u8 pad20[0xC];
} ResourceSlotStateView;

typedef struct ZoneLoadInfo {
    u8 pad00[0x234];
    s32 count;
    u32 word238;
    u32 refs[1];
} ZoneLoadInfo;

typedef struct ResourceHandler {
    s32 (*callback)(ResourceEntry *);
    s32 (*release)(ResourceEntry *);
    u32 words[5];
} ResourceHandler;

/* Shared owners confirmed by the lookup, allocation and unref units.
 * Offset aliases and the ambiguously typed D_8005CFBC table stay local. */
extern ResourceEntry *D_80057914;
extern ResourceSlot D_800580A0[];
extern ResourceBucket **D_8005C530;
extern ResourceBucket *D_8005C534;
extern ResourceHashMetadata *D_8005C540;
extern ResourcePool D_8005C91C;

s32 func_800126C0(ResourceHandle *handle);
s32 func_8001439C(void);
s32 func_80014514(s32 index);
void func_800148C4(ResourceSlot *slot);
void func_80014930(ResourceSlot *slot);
ResourceBucket *func_80015978(s32 id);
ResourceBucket *func_800159C4(u32 id);

#endif
