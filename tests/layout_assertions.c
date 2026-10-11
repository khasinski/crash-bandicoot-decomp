/* GCC_VERSION: 2.6.3 */
#include "engine_state.h"
#include "gool.h"
#include "object_links.h"
#include "resource.h"
#include "render.h"

/* Compile with the actual PS1 compiler. Host pointer sizes are irrelevant. */
#define SIZE(type, bytes) typedef char size_##type[(sizeof(type) == (bytes)) ? 1 : -1]
#define OFFSET(type, field, bytes) typedef char offset_##type##_##field[(CRASH_OFFSETOF(type, field) == (bytes)) ? 1 : -1]

SIZE(EngineState, 0x1C);
SIZE(EngineMode25State, 0x35D8);
OFFSET(EngineMode25State, word359C, 0x359C);
OFFSET(EngineMode25State, word35D0, 0x35D0);
OFFSET(EngineMode25State, word35D4, 0x35D4);
SIZE(EngineEventRequest, 12);
OFFSET(EngineEventRequest, pending, 4);
OFFSET(EngineEventRequest, event, 8);
SIZE(EngineByteRecord, 6);

OFFSET(ObjectView, resource, 0x10);
OFFSET(GoolRuntimeObject, entry, 0x28);
OFFSET(GoolRuntimeObject, word04, 4);
OFFSET(GoolRuntimeObject, next, 0x68);
OFFSET(GoolRuntimeObject, children, 0x6C);
OFFSET(GoolRuntimeObject, flagsCC, 0xCC);
OFFSET(GoolRuntimeObject, stack, 0xDC);
OFFSET(GoolRuntimeObject, pc, 0xE0);
OFFSET(GoolRuntimeObject, frame, 0xE4);
OFFSET(GoolRuntimeObject, flags120, 0x120);
OFFSET(GoolRuntimeObject, offset138, 0x138);
OFFSET(GoolResourceState, flags2DC, 0x2DC);
SIZE(GoolDefaults, 0x30);
OFFSET(GoolDefaultsObject, entry, 0x28);
OFFSET(GoolDefaultsObject, defaults, 0x30);
OFFSET(GoolMessageEntry, type, 4);
OFFSET(GoolMessageResource, entry, 0x10);
OFFSET(GoolActorView, bounds, 8);
OFFSET(GoolActorView, resource, 0x20);
OFFSET(GoolActorView, position, 0x80);
OFFSET(GoolActorView, radius, 0xB0);
SIZE(GoolMessage, 24);
OFFSET(GoolMessage, selector, 12);
OFFSET(GoolMessage, count, 16);
OFFSET(Node, next, 0x68);
OFFSET(Node, children, 0x6C);

SIZE(ResourceHandle, 8);
SIZE(ResourceEntry, 0x14);
OFFSET(ResourceEntry, kind, 8);
OFFSET(ResourceEntry, data, 0x10);
OFFSET(ResourceItemListView, items, 0x10);
OFFSET(ResourceItemSelection, word204, 0x204);
OFFSET(ResourceHeader, entries, 0x10);
SIZE(ResourceSlot, 0x2C);
OFFSET(ResourceSlot, state, 4);
OFFSET(ResourceSlot, references, 0xA);
OFFSET(ResourceSlot, id, 0x14);
OFFSET(ResourceSlot, base, 0x1C);
OFFSET(ResourceSlot, mapping, 0x20);
SIZE(ResourceBucket, 8);
OFFSET(ResourceBucket, id, 4);
OFFSET(ResourceHashMetadata, count, 0x404);
OFFSET(ResourcePool, active_count, 0x68C);
SIZE(ResourceSlotStateView, 0x2C);
OFFSET(ResourceSlotStateView, id, 0x10);
OFFSET(ResourceSlotStateView, id_pointer, 0x1C);
OFFSET(ZoneLoadInfo, count, 0x234);
OFFSET(ZoneLoadInfo, refs, 0x23C);
SIZE(ResourceHandler, 0x1C);

SIZE(GpuPacketHeader, 8);
SIZE(GpuRect, 8);
SIZE(GpuDrawEnv, 0x1C);
SIZE(GpuDisplayEnv, 0x14);
SIZE(GpuDrawing, 0x5C);
OFFSET(GpuDrawing, packet, 0x1C);
SIZE(GpuTile, 0x10);
OFFSET(RenderBuffer, display, 4);
OFFSET(RenderBuffer, drawing, 0x18);
OFFSET(RenderBuffer, word74, 0x74);
OFFSET(RenderBuffer, word78, 0x78);
OFFSET(RenderBuffer, ordering_table, 0x88);
SIZE(RenderBuffer, 0x2088);
SIZE(RenderTransformWords, 0x12);
