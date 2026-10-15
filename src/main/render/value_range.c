#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Select 0x11, 0x22 or 0x33 for the observed input ranges. */
s32 func_800175D0(s32 arg0)
{
    if (arg0 < 0) {
        arg0 = 0x22;
    } else if (arg0 < 0x13) {
        arg0 = 0x11;
    } else if (arg0 < 0x24) {
        arg0 = 0x22;
    } else if (arg0 < 0x35) {
        arg0 = 0x33;
    }
    return arg0;
}

typedef struct {
    u32 words[5];
    struct {
        u8 pad[3];
        u8 flags;
    } entries[1];
} RenderEntryData;

typedef struct {
    u8 pad00[0x10];
    RenderEntryData *data;
} RenderEntry;

extern s32 D_80056710;
void func_80015118(u32 *, s32, s32);
u32 func_80015978(u32);
void func_80015A98(u32 *);

s32 func_80017610(RenderEntry *entry)
{
    RenderEntryData *data = entry->data;
    u32 i;

    for (i = 0; i < data->words[6]; i++) {
        func_80015A98(&data->words[i + 8]);
    }
    return -0xFF;
}

s32 func_8001767C(RenderEntry *entry)
{
    RenderEntryData *data = entry->data;
    u32 i = 0;

    if (D_80056710 == 0x19 || D_80056710 == 0x38) {
        while (i < data->words[4]) {
            if (data->entries[i].flags & 0x80) {
                if (data->words[i + 6] & 1) {
                    data->words[i + 6] = func_80015978(data->words[i + 6]);
                }
                i += 3;
            } else {
                i += 1;
            }
        }
    } else {
        while (i < data->words[4]) {
            if (data->entries[i].flags & 0x80) {
                func_80015118(&data->words[i + 6], 0, 1);
                i += 3;
            } else {
                i += 1;
            }
        }
    }
    return -0xFF;
}
