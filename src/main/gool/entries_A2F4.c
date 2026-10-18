#include "common.h"

/* GCC_VERSION: 2.6.3 */

void func_80042E9C(void *);
void func_80042ECC(void *);
void func_80033FBC(void *, u32, s32);
s32 *func_80016E18(void);
void func_80035438(u16 *, s32, s32, s32, s32 *, void *);
void func_80035898(u16 *, s32, s32, s32, s32 *, void *);
void func_80035E10(u16 *, s32, s32, s32, s32 *, void *);
void func_80036340(u16 *, s32, s32, s32, s32 *, void *);
void func_80036BF4(u16 *, s32, s32, s32, s32 *, void *, u32, s32);
void func_800375EC(u16 *, s32, s32, s32, s32 *, void *);
void *func_80015A98(void *);

typedef struct ZoneFogHeader {
    u8 pad00[0x2E8];
    s32 depth_offset;
    s32 fog_mode;
} ZoneFogHeader;

extern struct {
    u8 pad[0x10];
    ZoneFogHeader *data;
} *D_80057914;

extern struct {
    s32 unk0;
    s32 type;
} *D_8005C53C;
extern struct {
    u8 pad000[0xAA8];
    s32 wordAA8;
    u8 padAAC[0xAC8 - 0xAAC];
    s32 wordAC8;
} D_80060DF0;

void func_80019AF4(u32 *arg0, s32 *arg1)
{
    s32 type;
    u32 offset;
    u32 val;
    s32 flag;

    type = D_8005C53C->type;
    if (type == 0x14 || type == 0x16) {
        offset = D_80060DF0.wordAA8 * 0xC80 + 0x64000;
        val = ((u32)D_80057914->data->depth_offset - offset) >> 8;
        D_80060DF0.wordAC8 = val + 0x7D0;
        flag = D_80057914->data->fog_mode;
        *arg0 = val;
    } else {
        val = (D_80057914->data->depth_offset - 0x32000) >> 8;
        flag = D_80057914->data->fog_mode;
        if (flag == 1) {
            val -= 0x4B0;
        }
        D_80060DF0.wordAC8 = val + 0x320;
        *arg0 = val;
    }
    *arg1 = flag;
}

