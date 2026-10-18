/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 4 */
#include "common.h"

void func_80042E9C(void *);
void func_80042ECC(void *);
void func_80033FBC(void *, u32, s32);
s32 *func_80016E18(void);
void func_800375EC(u16 *, s32, s32, s32, s32 *, void *);
void *func_80015A98(void *);

extern u16 *D_800566B8[];
extern u8 D_800577E4[];
extern struct {
    u8 pad[0x10];
    u8 *data;
} *D_80057914[];
extern s32 D_800578D0[];
extern s32 D_80057960[];
extern u8 D_80051774[];

extern void * D_800566B4;

typedef struct {
    u32 words[5];
    u8 *ptr14;
    u32 rest[10];
} ZoneItem64;

void func_8001A2E0(s32 arg0)
{
    s32 *data;
    s32 i;
    u32 dst;
    ZoneItem64 *ptr;

    data = (s32 *)D_80057914[0]->data;
    if (*D_800566B8[0] != 0) {
        func_80042E9C(D_800577E4);
        func_80042ECC(D_800577E4 + 0x110);
        func_80033FBC(data + 1, 0x1F800100, 0x100);
        dst = 0x1F800300;
        for (i = 0; i < *data; i++) {
            ptr = (ZoneItem64 *)((u32)data + (i << 6));
            func_80033FBC(ptr->ptr14, dst, 6);
            dst += 0x10;
        }
        *(s32 *)0x1F800048 = D_800566D4 >> 8;
        *(s32 *)0x1F80004C = D_800566D8 >> 8;
        *(s32 *)0x1F800050 = D_800566DC >> 8;
        *(s32 *)0x1F800054 = D_80056460;
        *(s32 *)0x1F800058 = D_80056464;
        *(s32 *)0x1F80005C = D_80056468;
        *(s32 *)0x1F800060 = D_8005646C;
        func_800375EC(D_800566B8[0], arg0, 0x800 - (D_800578D0[0] / 2), D_80057960[0], func_80016E18(), D_80051774);
    }
}

typedef struct {
    u32 pad00[3];
    u32 count;
} WgeoSubHeader;

typedef struct {
    u32 pad00[3];
    s32 item_count;
    WgeoSubHeader *sub;
    u32 pad14[2];
    u16 *list;
} WgeoEntry;

void func_8001A460(u32 arg0, u32 arg1)
{
    u8 *data;
    s32 group;
    s32 count;
    ZoneItem64 *base;
    s32 j;
    WgeoEntry *res;
    u16 *list;
    WgeoSubHeader *sub;
    s32 len;
    s32 i;
    u16 item;
    u32 idx;
    u32 *target;

    data = D_80057914[0]->data;
    group = -1;
    count = *(s32 *)data;
    base = (ZoneItem64 *)(data + 4);
    for (j = 0; j < count; j++) {
        res = func_80015A98(&base[j]);
        if (res->item_count >= 4) {
            list = res->list;
            len = list[0];
            sub = res->sub;
            for (i = 1; i < len + 1; i++) {
                item = list[i];
                if (item & 0x8000) {
                    group = item & 0xFFF;
                } else {
                    idx = item & 0xFFF;
                    if (idx < sub->count) {
                        target = (u32 *)(base[j].ptr14 + (idx << 3));
                        if (group < 32) {
                            if (arg0 & (1 << group)) {
                                goto set_flag;
                            }
                            target[1] &= ~0x1E;
                        } else if (arg1 & (1 << (group - 32))) {
                        set_flag:
                            target[1] = (target[1] & ~0x1E) | 0xF;
                        } else {
                            target[1] &= ~0x1E;
                        }
                    }
                }
            }
        }
    }
}

typedef struct {
    u8 bytes[4];
    u32 word;
} AnimSpriteDesc;

void func_8001A5F4(s32 arg0, u8 *arg1, s32 arg2, s16 *arg3)
{
    AnimSpriteDesc *ptr;
    u32 res;
    u32 word;
    s16 y;
    s16 x;
    u8 *table_entry;
    s32 val;

    switch (*arg1) {
    case 2:
        ptr = (AnimSpriteDesc *)(arg1 + (((arg2 >> 8) << 3) + 8));
        break;
    case 5:
        ptr = (AnimSpriteDesc *)(arg1 + (((arg2 >> 8) << 4) + 12));
        break;
    }
    res = (u32)func_80015A98(arg1 + 4);
    word = ptr->word;
    switch (arg0) {
    case 2:
        y = ((res >> 10) & 0x180) | ((word >> 6) & 0x7F);
        x = (res & 0x300) | ((ptr->bytes[3] & 0xF) << 4);
        arg3[1] = y;
        arg3[0] = x;
        if (!((word >> 20) & 3)) {
            arg3[2] = 0x10;
        } else {
            arg3[2] = 0x100;
        }
        arg3[3] = 1;
        break;
    case 1:
        arg3[0] = (res & 0x300) | ((word >> 12) & 0xFE);
        arg3[1] = ((res >> 10) & 0x180) | ((word << 2) & 0x7C);
        table_entry = D_80051774 + ((word >> 22) << 3);
        val = table_entry[2] + 1;
        arg3[2] = ((word >> 20) & 3) ? (val >> 1) : (val >> 2);
        arg3[3] = table_entry[5] + 1;
        break;
    }
}

void func_8001A754(u8 *arg0, s32 arg1, u8 *arg2, s32 arg3)
{
    s32 offset;
    s32 i;
    u8 ch;

    offset = 0;
    arg1 >>= 8;
    for (i = 0; i < arg1; i++) {
        for (; *(arg0 + offset + 0xC) != 0; offset++)
            ;
        offset++;
    }
    for (i = 0; arg3 != 0 && *arg2 != 0; arg2++, arg3--, i++) {
        ch = *arg2;
        ch &= 0x7F;
        if (ch < 0x20) {
            ch = 0x20;
        }
        if (ch == 0x7B) {
            ch = 0x28;
        }
        if (ch == 0x7D) {
            ch = 0x29;
        }
        if (ch == 0x7E) {
            ch = 0x7B;
        }
        if (ch == 0x25) {
            ch = 0x7D;
        }
        *(arg0 + (offset + i) + 0xC) = ch;
    }
    for (; arg3 != 0; arg3--, i++) {
        *(arg0 + (offset + i) + 0xC) = 0x20;
    }
}

void func_80040484(s16 *, u8 *);
void func_800404E8(s16 *, u8 *);
void func_8004025C(s32);

void func_8001A850(s32 arg0, u8 *arg1, s32 arg2, u8 *arg3, u8 *arg4)
{
    u8 buf[0x200];
    s16 rect[4];
    u8 *aligned;
    s32 i;

    aligned = (u8 *)(((u32)buf + 0x100) & ~0xFF);
    if (arg3 != NULL) {
        func_8001A5F4(2, arg1, arg2, rect);
        if (arg0 == 1) {
            for (i = 0; i < rect[2] * rect[3] * 2; i++) {
                aligned[i] = arg3[i];
            }
            func_80040484(rect, aligned);
        } else {
            func_800404E8(rect, aligned);
            func_8004025C(0);
            for (i = 0; i < rect[2] * rect[3] * 2; i++) {
                arg3[i] = aligned[i];
            }
        }
    }
    if (arg4 != NULL) {
        func_8001A5F4(1, arg1, arg2, rect);
        if (arg0 == 1) {
            for (i = 0; i < rect[2] * rect[3] * 2; i++) {
                aligned[i] = arg4[i];
            }
            func_80040484(rect, aligned);
        } else {
            func_800404E8(rect, aligned);
            func_8004025C(0);
            for (i = 0; i < rect[2] * rect[3] * 2; i++) {
                arg4[i] = aligned[i];
            }
        }
    }
}

void *LIBC_Malloc(u32);

typedef struct GoolObj {
    s32 header;
    u8 pad04[0x60 - 0x04];
    struct GoolObj *self;
    void *parent;
    struct GoolObj *sibling;
    struct GoolObj *child;
    u8 pad70[0x25C - 0x70];
} GoolObj;

typedef struct GoolAllocGlobals {
    GoolObj *db0;
    GoolObj *db4;
    s32 db8[16];
    s32 df8;
    GoolObj *dfc;
    void *e00;
    s32 e04;
} GoolAllocGlobals;

extern GoolAllocGlobals gool_alloc_state __asm__("gool_alloc");
extern GoolObj * volatile gool_alloc[2];
extern s32 D_80060DB8[];
extern s32 D_80060DF8[];
extern void *D_80060E00[];
extern s32 D_80060E04[];

s32 GOOL_InitAllocTable(void)
{
    s32 i;
    GoolObj *obj;

    D_800566B4 = NULL;
    gool_alloc_state.db4 = LIBC_Malloc(0xE280);
    gool_alloc_state.db0 = LIBC_Malloc(0x35C);
    if (gool_alloc_state.db4 == NULL || gool_alloc_state.db0 == NULL) {
        return -0xF;
    }
    D_80060E00[0] = NULL;
    D_80060E04[0] = 0;
    D_80060DF8[0] = 2;
    gool_alloc_state.dfc = gool_alloc_state.db4;
    for (i = 0; i < 0x60; i++) {
        obj = &gool_alloc_state.db4[i];
        obj->header = 0;
        obj->parent = &gool_alloc_state.df8;
        obj->child = NULL;
        if (i < 0x5F) {
            obj->sibling = &gool_alloc_state.db4[i + 1];
        } else {
            obj->sibling = NULL;
        }
    }
    for (i = 0; i < 8; i++) {
        D_80060DB8[i * 2] = 2;
        D_80060DB8[i * 2 + 1] = 0;
    }
    gool_alloc[0]->header = 0;
    gool_alloc[0]->parent = NULL;
    gool_alloc[0]->child = NULL;
    gool_alloc[0]->sibling = NULL;
    return -0xFF;
}
