/* GCC_VERSION: 2.6.3 */
#include "common.h"

u8 *func_80043A24(s32, u8 *);
s32 func_80043520(u8, u8 *, u8 *);
s32 func_800439A4(s32, void *, s32);
s32 func_80043984(s32, void *);

s32 func_8002F858(s32 sector_count, s32 first_sector, void *destination)
{
    u8 position[3];
    func_80043A24(first_sector, position);
    func_80043520(2, position, NULL);
    func_800439A4(sector_count, destination, 0x80);
    return func_80043984(0, NULL) == 0;
}
