/* GCC_VERSION: 2.6.3 */
#include "common.h"

u8 *CdIntToPos(s32, u8 *);
s32 CdControl(u8, u8 *, u8 *);
s32 CdRead(s32, void *, s32);
s32 CdReadSync(s32, void *);

s32 Cd_ReadSectors(s32 sector_count, s32 first_sector, void *destination)
{
    u8 position[3];
    CdIntToPos(first_sector, position);
    CdControl(2, position, NULL);
    CdRead(sector_count, destination, 0x80);
    return CdReadSync(0, NULL) == 0;
}
