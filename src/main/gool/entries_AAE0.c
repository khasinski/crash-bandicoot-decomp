/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 4 */
#include "common.h"

void SetRotMatrix(void *);
void SetLightMatrix(void *);
void RMemcpy(void *, u32, s32);
s32 *Gpu_GetCurPrimsTail(void);
void Gte_RTransformWorldsDark2(u16 *, s32, s32, s32, s32 *, void *);
void *Ns_Lookup(void *);

extern u16 *gp_level_entry[];
extern struct {
    u8 pad[0x10];
    u8 *data;
} *g_pads[];
extern s32 g_view_proj[];
extern s32 g_draw_stamp[];

extern void * gp_crash_obj;

typedef struct {
    u32 words[5];
    u8 *ptr14;
    u32 rest[10];
} ZoneItem64;

void Gfx_TransformWorldsDark2(s32 arg0)
{
    s32 *data;
    s32 i;
    u32 dst;
    ZoneItem64 *ptr;

    data = (s32 *)g_pads[0]->data;
    if (*gp_level_entry[0] != 0) {
        SetRotMatrix(g_m_view);
        SetLightMatrix(g_m_view + 0x110);
        RMemcpy(data + 1, 0x1F800100, 0x100);
        dst = 0x1F800300;
        for (i = 0; i < *data; i++) {
            ptr = (ZoneItem64 *)((u32)data + (i << 6));
            RMemcpy(ptr->ptr14, dst, 6);
            dst += 0x10;
        }
        *(s32 *)0x1F800048 = D_800566D4 >> 8;
        *(s32 *)0x1F80004C = D_800566D8 >> 8;
        *(s32 *)0x1F800050 = D_800566DC >> 8;
        *(s32 *)0x1F800054 = gp_dark_cone_rot;
        *(s32 *)0x1F800058 = D_80056464;
        *(s32 *)0x1F80005C = D_80056468;
        *(s32 *)0x1F800060 = D_8005646C;
        Gte_RTransformWorldsDark2(gp_level_entry[0], arg0, 0x800 - (g_view_proj[0] / 2), g_draw_stamp[0], Gpu_GetCurPrimsTail(), D_80051774);
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

void Gfx_FreezeMapTextures(u32 arg0, u32 arg1)
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

    data = g_pads[0]->data;
    group = -1;
    count = *(s32 *)data;
    base = (ZoneItem64 *)(data + 4);
    for (j = 0; j < count; j++) {
        res = Ns_Lookup(&base[j]);
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

void Gfx_GetIconTexinfo(s32 arg0, u8 *arg1, s32 arg2, s16 *arg3)
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
    res = (u32)Ns_Lookup(arg1 + 4);
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

void Gfx_FormatCardString(u8 *arg0, s32 arg1, u8 *arg2, s32 arg3)
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

void LoadImage(s16 *, u8 *);
void StoreImage(s16 *, u8 *);
void DrawSync(s32);

void Gfx_BlitCardIcon(s32 arg0, u8 *arg1, s32 arg2, u8 *arg3, u8 *arg4)
{
    u8 buf[0x200];
    s16 rect[4];
    u8 *aligned;
    s32 i;

    aligned = (u8 *)(((u32)buf + 0x100) & ~0xFF);
    if (arg3 != NULL) {
        Gfx_GetIconTexinfo(2, arg1, arg2, rect);
        if (arg0 == 1) {
            for (i = 0; i < rect[2] * rect[3] * 2; i++) {
                aligned[i] = arg3[i];
            }
            LoadImage(rect, aligned);
        } else {
            StoreImage(rect, aligned);
            DrawSync(0);
            for (i = 0; i < rect[2] * rect[3] * 2; i++) {
                arg3[i] = aligned[i];
            }
        }
    }
    if (arg4 != NULL) {
        Gfx_GetIconTexinfo(1, arg1, arg2, rect);
        if (arg0 == 1) {
            for (i = 0; i < rect[2] * rect[3] * 2; i++) {
                aligned[i] = arg4[i];
            }
            LoadImage(rect, aligned);
        } else {
            StoreImage(rect, aligned);
            DrawSync(0);
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

extern GoolAllocGlobals gool_alloc;
extern GoolObj * volatile g_player[];
extern s32 D_80060DF8[];
extern void *g_savestate[];

s32 GOOL_InitAllocTable(void)
{
    s32 i;
    GoolObj *obj;

    gp_crash_obj = NULL;
    gool_alloc.db4 = LIBC_Malloc(0xE280);
    gool_alloc.db0 = LIBC_Malloc(0x35C);
    if (gool_alloc.db4 == NULL || gool_alloc.db0 == NULL) {
        return -0xF;
    }
    g_savestate[0] = NULL;
    D_80060E04[0] = 0;
    D_80060DF8[0] = 2;
    gool_alloc.dfc = gool_alloc.db4;
    for (i = 0; i < 0x60; i++) {
        obj = &gool_alloc.db4[i];
        obj->header = 0;
        obj->parent = &gool_alloc.df8;
        obj->child = NULL;
        if (i < 0x5F) {
            obj->sibling = &gool_alloc.db4[i + 1];
        } else {
            obj->sibling = NULL;
        }
    }
    for (i = 0; i < 8; i++) {
        ((s32 *)g_free_objects)[i * 2] = 2;
        ((s32 *)g_free_objects)[i * 2 + 1] = 0;
    }
    g_player[0]->header = 0;
    g_player[0]->parent = NULL;
    g_player[0]->child = NULL;
    g_player[0]->sibling = NULL;
    return -0xFF;
}
