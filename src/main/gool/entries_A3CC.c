/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"

void func_80042E9C(void *);
void func_80042ECC(void *);
void func_80033FBC(void *, u32, s32);
s32 *func_80016E18(void);
void func_80035898(u16 *, s32, s32, s32, s32 *, void *);
void func_80036BF4(u16 *, s32, s32, s32, s32 *, void *, u32, s32);

typedef struct ZoneFogHeader {
    u8 pad00[0x2E8];
    s32 depth_offset;
    s32 fog_mode;
} ZoneFogHeader;

typedef struct ZoneHeader {
    u8 pad[0x10];
    ZoneFogHeader *data;
} ZoneHeader;

typedef struct NsdHeader {
    s32 unk0;
    s32 type;
} NsdHeader;

extern u16 *D_800566B8[];
extern u8 D_800577E4[];
extern ZoneHeader *D_80057914[];
extern s32 D_800578D0[];
extern s32 D_80057960[];
extern u8 D_80051774[];
extern NsdHeader *D_8005C53C[];

extern struct {
    u8 pad000[0xAA8];
    s32 wordAA8;
    u8 padAAC[0xAC8 - 0xAAC];
    s32 wordAC8;
} D_80060DF0;

static __inline__ void func_80019AF4(u32 *arg0, s32 *arg1)
{
    s32 type;
    u32 offset;
    u32 val;
    s32 flag;

    type = D_8005C53C[0]->type;
    if (type == 0x14 || type == 0x16) {
        offset = D_80060DF0.wordAA8 * 0xC80 + 0x64000;
        val = ((u32)D_80057914[0]->data->depth_offset - offset) >> 8;
        D_80060DF0.wordAC8 = val + 0x7D0;
        flag = D_80057914[0]->data->fog_mode;
        *arg0 = val;
    } else {
        val = (D_80057914[0]->data->depth_offset - 0x32000) >> 8;
        flag = D_80057914[0]->data->fog_mode;
        if (flag == 1) {
            val -= 0x4B0;
        }
        D_80060DF0.wordAC8 = val + 0x320;
        *arg0 = val;
    }
    *arg1 = flag;
}

#define GOOL_CALC_FOG(arg0, arg1) \
    { \
        u32 *_arg0 = (arg0); \
        s32 _type; \
        u32 _offset; \
        u32 _val; \
        s32 _flag; \
        s32 _zero = 0; \
        do { } while (0); \
        if (_zero) { \
            if (D_8005C53C[0]) { _offset = 1; _zero = 1; } \
            _zero = 2; \
        } \
        _type = D_8005C53C[0]->type; \
        if (_type == 0x14 || _type == 0x16) { \
            _offset = D_80060DF0.wordAA8 * 0xC80 + 0x64000; \
            _val = ((u32)D_80057914[0]->data->depth_offset - _offset) >> 8; \
            D_80060DF0.wordAC8 = _val + 0x7D0; \
            _flag = D_80057914[0]->data->fog_mode; \
            *_arg0 = _val; \
        } else { \
            _val = (D_80057914[0]->data->depth_offset - 0x32000) >> 8; \
            _flag = D_80057914[0]->data->fog_mode; \
            if (_flag == 1) { \
                _val -= 0x4B0; \
            } \
            D_80060DF0.wordAC8 = _val + 0x320; \
            *_arg0 = _val; \
        } \
        *(arg1) = _flag; \
    }

typedef struct {
    u8 pad00[0x1C];
    s32 flags;
} WgeoHeaderView;

typedef struct {
    u32 word0;
    u32 pad[3];
    WgeoHeaderView *ptr10;
    u32 pad2[11];
} GoolEntry64;

typedef struct {
    s32 count;
    u32 data[1];
} GoolAnimData;

void func_80019BCC(s32 arg0)
{
    GoolAnimData *data;
    u32 sp18;
    s32 sp1C;
    s32 i;
    GoolEntry64 *base;

    base = (GoolEntry64 *)0x1F800100;
    data = (GoolAnimData *)D_80057914[0]->data;
    if (*D_800566B8[0] != 0) {
        func_80042E9C(D_800577E4);
        func_80042ECC(D_800577E4 + 0x110);
        func_80033FBC(data->data, (u32)base, data->count << 5);
        GOOL_CALC_FOG(&sp18, &sp1C);
        for (i = 0; i < data->count; i++) {
            if (base[i].ptr10->flags == 1) {
                *(u32 *)(base + i) = (sp1C << 16) | 0xFFFF;
            } else {
                *(u32 *)(base + i) = (sp1C << 16) | sp18;
            }
        }
        func_80035898(D_800566B8[0], arg0, 0x800 - (D_800578D0[0] / 2), D_80057960[0], func_80016E18(), D_80051774);
    }
}

