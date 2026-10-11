/* GCC_VERSION: 2.6.3 */
#include "gpu.h"
typedef struct {GpuDrawEnv env;u32 packet[16];} Drawing;
typedef struct {GpuPacketHeader header;GpuRect rect;} Tile;
GpuDrawEnv *func_8003F408(GpuDrawEnv *,s16,s16,s16,s32);
void *func_80040834(Drawing *);
void func_8003F7D8(u32 *);
void func_8003FA14(GpuPacketHeader *);
s32 func_80040760(GpuPacketHeader *);
void func_8001696C(void) {
    Drawing drawing;
    Tile tile;
    func_8003F408(&drawing.env,0,0,1024,512);
    drawing.env.draw_to_display = 1;
    func_80040834(&drawing);
    func_8003F7D8((u32 *)&tile);
    func_8003FA14(&tile.header);
    tile.rect.w = 1023;
    tile.rect.h = 511;
    tile.header.color[0] = 0;
    tile.header.color[1] = 0;
    tile.header.color[2] = 0;
    tile.rect.x = 0;
    tile.rect.y = 0;
    func_80040760(&tile.header);
}
