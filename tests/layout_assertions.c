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
OFFSET(EngineMode25State, word00, 0);
OFFSET(EngineMode25State, word0C, 0xC);
OFFSET(EngineMode25State, word18, 0x18);
OFFSET(EngineMode25State, word359C, 0x359C);
OFFSET(EngineMode25State, word3598, 0x3598);
OFFSET(EngineMode25State, word35A0, 0x35A0);
OFFSET(EngineMode25State, word35A4, 0x35A4);
OFFSET(EngineMode25State, word35D0, 0x35D0);
OFFSET(EngineMode25State, word35D4, 0x35D4);
SIZE(EngineFileRequest, 12);
OFFSET(EngineFileRequest, pending, 4);
OFFSET(EngineFileRequest, path, 8);
SIZE(EngineByteRecord, 6);
SIZE(EngineSaveRecord, 0x80);
OFFSET(EngineSaveRecord, word04, 4);
OFFSET(EngineSaveRecord, word20, 0x20);
OFFSET(EngineSaveRecord, word24, 0x24);
OFFSET(EngineSaveRecord, checksum, 0x7C);
SIZE(EngineCardHeader, 0x80);
OFFSET(EngineCardHeader, title, 4);
OFFSET(EngineCardHeader, palette, 0x60);
SIZE(EngineCardBlock, 0x80);
SIZE(EngineDirectoryRecord, 0x28);
SIZE(EngineDirectorySlot, 0x4C);
OFFSET(EngineDirectorySlot, record_index, 8);
SIZE(EngineDirectoryState, 0x6F4);
OFFSET(EngineDirectoryState, word1C, 0x1C);
OFFSET(EngineDirectoryState, word20, 0x20);
OFFSET(EngineDirectoryState, slots, 0x28);
OFFSET(EngineDirectoryState, records, 0x49C);

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
SIZE(ResourceMapMetadata, 16);
OFFSET(ResourceMapMetadata, count, 12);
OFFSET(ResourceMapItem, word18, 0x18);
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
OFFSET(RenderContextView, word114, 0x114);
SIZE(RenderProjectionState, 0x18);
OFFSET(RenderProjectionState, matrix, 4);
OFFSET(RenderCameraPrefix, projection, 0x6C);
