#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Call the CD routine with the inverted flag; report success only for a zero result. */

extern s32 func_80043984(s32, s32);

s32 func_8001381C(s32 enabled)
{
    s32 result = func_80043984(enabled == 0, 0);
    if (result < 0)
        return 0;
    return result == 0;
}

typedef struct CdResourceHash {
    u8 pad00[0x418];
    s32 word418;
    s32 word41C;
    u32 words420[1];
} CdResourceHash;

typedef struct CdResourceSlot {
    u8 *header;
    u16 state;
    s16 word06;
    s16 word08;
    s16 references;
    s16 word0C;
    s16 word0E;
    u32 word10;
    s32 id;
} CdResourceSlot;

extern void *D_8005C540;
extern s32 D_8005C548;
extern u8 *func_80043A24(s32, u8 *);
extern s32 func_80043668(u8, u8 *);
extern s32 func_800439A4(s32, void *, s32);

s32 func_8001384C(CdResourceSlot *slot, s32 count)
{
    u8 loc[16];
    s32 id;
    s32 sectors;
    u8 *buf;
    s32 pos;

    id = slot->id;
    if (slot->word0E != 0) {
        sectors = (count << 5) - slot->word0C;
        buf = slot->header + (slot->word0C << 11);
        pos = D_8005C548 + (((CdResourceHash *)D_8005C540)->words420[id >> 1] >> 6);
    } else {
        sectors = count << 5;
        pos = D_8005C548 + ((CdResourceHash *)D_8005C540)->word418 + ((id >> 1) << 5);
        buf = slot->header;
    }
    func_80043A24(pos, loc);
    func_80043668(2, loc);
    if (func_800439A4(sectors, buf, 0x80) == 0) {
        return -0x10;
    }
    return -0xFF;
}

