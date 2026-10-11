#ifndef CRASH_GOOL_H
#define CRASH_GOOL_H

#include "common.h"

/* Partial view for routines accessing the resource pointer at offset 0x10.
 * This is not yet a reconstruction of the full object/resource layout.
 */
typedef struct ObjectView {
    u8 pad00[0x10];
    u8 *resource;
} ObjectView;

/* Runtime object view assembled from release, frame restore and flag access.
 * Unknown bytes remain padding; this is a prefix, not the full object size.
 * entry is a tagged word, not an unconditionally dereferenceable pointer. */
typedef struct GoolRuntimeObject {
    s32 kind;
    struct GoolRuntimeObject *word04;
    u8 pad08[0x20];
    s32 entry;
    u8 pad2C[0x3C];
    struct GoolRuntimeObject *next;
    struct GoolRuntimeObject *children;
    u8 pad70[0x5C];
    u32 flagsCC;
    u8 padD0[0xC];
    u32 *stack;
    u32 pc;
    u32 *frame;
    u8 padE8[0x38];
    u32 flags120;
    u8 pad124[0x14];
    s32 offset138;
} GoolRuntimeObject;

/* Independent view of the resource reached through ObjectView.resource. */
typedef struct GoolResourceState {
    u8 pad00[0x2DC];
    u32 flags2DC;
} GoolResourceState;

/* Default block copied by func_8001EA00; halfword updates at 0x2A..0x2E. */
typedef struct GoolDefaults {
    u8 bytes[0x2A];
    u16 field2A, field2C, field2E;
} GoolDefaults;

struct ResourceEntry;
typedef struct GoolDefaultsObject {
    u8 pad00[0x28];
    struct ResourceEntry *entry;
    u32 word2C;
    GoolDefaults defaults;
} GoolDefaultsObject;

/* Message/collision view from func_80024CC8. Its resource points to a
 * two-word entry prefix whose type is at +4, unlike ResourceEntry.kind (+8).
 * Keep that distinct format explicit rather than merging by similar names. */
typedef struct GoolMessageEntry {
    s32 word00, type;
} GoolMessageEntry;

typedef struct GoolMessageResource {
    u8 pad00[0x10];
    GoolMessageEntry *entry;
} GoolMessageResource;

typedef struct GoolActorView {
    u8 pad00[8];
    s32 bounds[6];
    GoolMessageResource *resource;
    u8 pad24[0x5C];
    s32 position[3];
    u8 pad8C[0x24];
    s32 radius[3];
} GoolActorView;

typedef struct GoolMessage {
    GoolActorView *source;
    s32 word04, word08, selector, count, word14;
} GoolMessage;

s32 func_8001D97C(GoolRuntimeObject *object, s32 *flags);
GoolRuntimeObject *GOOL_TestObjectStateFlags(GoolRuntimeObject *, u32 flags);
void func_8001EA00(GoolDefaultsObject *object, s32 mode);
void func_800257B4(ObjectView *object);
void func_80025804(ObjectView *object);
void func_80027A08(GoolRuntimeObject *object, s32 index, s32 fallback);

#endif
