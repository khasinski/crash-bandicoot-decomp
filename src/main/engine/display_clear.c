/* GCC_VERSION: 2.6.3 */
#include "gpu.h"
typedef GpuDrawing Drawing;
typedef GpuTile Tile;

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
