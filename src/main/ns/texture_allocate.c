/* GCC_VERSION: 2.6.3 */
/* CC1_FLAGS: -O2 -fno-cse-follow-jumps */
#include "common.h"
#include "resource.h"

typedef struct
{
    u8 pad00[0x234];
    s32 count;
    u32 word238;
    u32 refs[1];
} ZoneLoadInfo;

extern ResourceEntry *D_80057914;

extern ResourceSlot D_800580A0[];

extern s16 D_800580A4[];

extern s32 D_800580B8[];

s32 func_80014514(s32);

/* Prefer free or inactive slots; otherwise evict a texture absent from the
 * current zone load list. Odd references are IDs, even references are entries.
 */
s32 func_8001439C(void)
{
    s32 i;
    s32 j;
    s32 used;
    s32 offset;
    s32 wanted;
    u32 bias;
    ResourceSlot *slot;
    ResourceSlot *scan_slot;
    s32 scan_offset;
    ZoneLoadInfo *zone;
    u32 ref;
    u32 id;
    i = 15;
    wanted = 1;
    scan_slot = &D_800580A0[15];
    do
    {
        if (((s16) scan_slot->state) == wanted)
            goto found;
        i--;
        scan_slot--;
    }
    while (i >= 0);
    i = 15;
    wanted = 21;
    scan_offset = 15 * 44;
    do
    {
        if ((*((s16 *) (((u8 *) D_800580A4) + scan_offset))) == wanted)
            goto found;
        i--;
        scan_offset -= 44;
    }
    while (i >= 0);
    i = 15;
    if (D_80057914 != NULL)
        goto search;
    func_80014514(15);
    return 15;
    recycle:
    func_80014514(i);

    found:
    return i;

    search:
    bias = 0xFFEC;

    zone = (ZoneLoadInfo *) D_80057914->data;
    offset = 15 * 44;
    slot = &D_800580A0[15];
    do
    {
        used = 0;
        if (((u16) (slot->state + bias)) < 2)
        {
            for (j = 0; j < zone->count; j++)
            {
                id = *((u32 *) (((u8 *) D_800580B8) + offset));
                ref = zone->refs[j];
                if (ref & 1)
                {
                    if (ref == id)
                        goto hit;
                }
                else
                    if (((ResourceEntry *) ref)->id == id)
                    goto hit;
                continue;
                hit:
                used = 1;

                break;
            }

            if (!used)
                goto recycle;
        }
        offset -= 44;
        i--;
        slot--;
    }
    while (i >= 0);
    return -12;
}
