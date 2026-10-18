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

extern struct {
    u8 pad[0x10];
    u8 *data;
} *D_80057914;
extern s32 D_80057960;

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

extern void * D_800566B4;
asm(".sdata\n.size D_800566B4,4\n.text");
extern void *D_80060E00;
extern s32 D_80060E04;

void func_8001D33C(u8 *arg0, s32 *arg1)
{
    s32 bounds[6];
    u8 *anim;
    u8 **res;
    u8 *model;
    s32 scale_x;
    s32 *box;
    s32 abs_x;
    s32 val;

    anim = *(u8 **)(arg0 + 0x108);
    if (anim == NULL) {
        return;
    }
    if (*anim != 4) {
        if ((((u32)(anim + 4) & 0xFF800003) != 0x80000000) || ((s32)func_80015A98(anim + 4) >= -0xFE)) {
            return;
        }
    }
    if (**(u8 **)(arg0 + 0x108) == 1) {
        res = func_80015A98(*(u8 **)(arg0 + 0x108) + 4);
        scale_x = arg1[0];
        model = res[(*(u32 *)(arg0 + 0x10C) >> 8) + 4];
        if (scale_x < 0) {
            arg1[0] = -scale_x;
        }
        if (arg0 == D_800566B4) {
            bounds[0] = *(s32 *)(model + 0x2C) + *(s32 *)(model + 0x14);
            bounds[1] = *(s32 *)(model + 0x30) + *(s32 *)(model + 0x18);
            bounds[2] = *(s32 *)(model + 0x34) + *(s32 *)(model + 0x1C);
            bounds[3] = *(s32 *)(model + 0x2C) + *(s32 *)(model + 0x20);
            bounds[4] = *(s32 *)(model + 0x30) + *(s32 *)(model + 0x24);
            bounds[5] = *(s32 *)(model + 0x34) + *(s32 *)(model + 0x28);
            box = bounds;
        } else {
            box = (s32 *)(model + 0x14);
        }
        *(s32 *)(arg0 + 0x8) = ((box[0] >> 8) * arg1[0]) >> 4;
        *(s32 *)(arg0 + 0xC) = ((box[1] >> 8) * arg1[1]) >> 4;
        *(s32 *)(arg0 + 0x10) = ((box[2] >> 8) * arg1[2]) >> 4;
        *(s32 *)(arg0 + 0x14) = ((box[3] >> 8) * arg1[0]) >> 4;
        *(s32 *)(arg0 + 0x18) = ((box[4] >> 8) * arg1[1]) >> 4;
        *(s32 *)(arg0 + 0x1C) = ((box[5] >> 8) * arg1[2]) >> 4;
        arg1[0] = scale_x;
    } else {
        abs_x = arg1[0] >= 0 ? arg1[0] : -arg1[0];
        val = (abs_x * 200) >> 4;
        *(s32 *)(arg0 + 0x14) = val;
        *(s32 *)(arg0 + 0x8) = -val;
        val = (arg1[1] * 200) >> 4;
        *(s32 *)(arg0 + 0x18) = val;
        *(s32 *)(arg0 + 0xC) = -val;
        val = (arg1[2] * 200) >> 4;
        *(s32 *)(arg0 + 0x1C) = val;
        *(s32 *)(arg0 + 0x10) = -val;
    }
    *(s32 *)(arg0 + 0x98) = arg1[0];
    *(s32 *)(arg0 + 0x9C) = arg1[1];
    *(s32 *)(arg0 + 0xA0) = arg1[2];
}

extern struct {
    u8 pad[0x7C];
    u32 stamp;
} *D_80058408;
extern s32 D_80061888;
extern s32 D_800619C8;
void GOOL_UpdateObject(void *, s32);
void func_8001B84C(void *, void *, s32);

typedef struct GoolUpdateGlobals {
    s32 db8[16];
    s32 df8;
    u8 *dfc;
    void *e00;
    s32 e04;
} GoolUpdateGlobals;

extern GoolUpdateGlobals gool_update __asm__("D_80060DB8");

void func_8001D5EC(s32 arg0)
{
    s32 i;
    s32 *ptr;

    D_80061888 = 0;
    D_800619C8 = D_80057960;
    gool_update.e04 = D_80058408->stamp / 34;
    if (D_800566B4 != NULL) {
        i = 0;
        ptr = gool_update.db8;
        do {
            func_8001B84C(ptr, GOOL_UpdateObject, arg0);
            i++;
            ptr += 2;
        } while (i < 8);
    }
}

s32 GOOL_CreateObjectStackFrame(void *, s32, s32);
s32 GOOL_InterpretObject(void *, s32, s32);

s32 GOOL_ChangeObjectState(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3)
{
    u32 saved_f0;
    u8 *state_desc;
    s32 i;

    saved_f0 = *(u32 *)(arg0 + 0xF0);
    if (arg1 == 0xFF || (*(u32 *)(arg0 + 0xCC) & 0x10000000)) {
        return -0xE;
    }
    *(s32 *)(arg0 + 0x2C) = arg1;
    state_desc = *(u8 **)(*(u8 **)(arg0 + 0x20) + 0x20) + (arg1 << 4);
    *(u32 *)(arg0 + 0xD0) = *(u32 *)(state_desc + 4);
    *(u8 **)(arg0 + 0x24) = func_80015A98(*(u8 **)(*(u8 **)(arg0 + 0x20) + 0x18) + (*(u16 *)(state_desc + 8) << 2));
    *(u8 **)(arg0 + 0xE0) = (*(u16 *)(state_desc + 0xE) != 0x3FFF)
        ? *(u8 **)(*(u8 **)(arg0 + 0x24) + 0x14) + (*(u16 *)(state_desc + 0xE) << 2)
        : NULL;
    *(u8 **)(arg0 + 0xEC) = (*(u16 *)(state_desc + 0xA) != 0x3FFF)
        ? *(u8 **)(*(u8 **)(arg0 + 0x24) + 0x14) + (*(u16 *)(state_desc + 0xA) << 2)
        : NULL;
    *(u8 **)(arg0 + 0xE8) = (*(u16 *)(state_desc + 0xC) != 0x3FFF)
        ? *(u8 **)(*(u8 **)(arg0 + 0x24) + 0x14) + (*(u16 *)(state_desc + 0xC) << 2)
        : NULL;
    *(u32 *)(arg0 + 0xF0) = 0;
    *(u8 **)(arg0 + 0xE4) = arg0 + 0x60;
    *(u8 **)(arg0 + 0xDC) = arg0 + ((*(s32 *)(*(u8 **)(*(u8 **)(arg0 + 0x20) + 0x10) + 0xC) << 2) + 0x60);
    *(u32 *)(arg0 + 0x120) = *(u32 *)state_desc;
    *(u32 *)(arg0 + 0xC8) |= 0x20020;
    for (i = 0; i < arg2; i++) {
        *(*(s32 ***)(arg0 + 0xDC))++ = arg3[i];
    }
    GOOL_CreateObjectStackFrame(arg0, arg2, 0xFFFF);
    if (saved_f0 != 0) {
        GOOL_CreateObjectStackFrame(arg0, 0, 0xFFFF);
        *(u32 *)(arg0 + 0xE0) = saved_f0;
        i = GOOL_InterpretObject(arg0, 0x13, 0);
        if (i >= -0xFE) {
            return i;
        }
    } else {
        *(*(s32 ***)(arg0 + 0xDC))++ = 0;
    }
    *(s32 *)(arg0 + 0x100) = D_80060E04;
    if (*(u8 **)(arg0 + 0xE8) != NULL && arg0 == D_80060E00) {
        GOOL_CreateObjectStackFrame(arg0, 0, 0xFFFF);
        *(u8 **)(arg0 + 0xE0) = *(u8 **)(arg0 + 0xE8);
        i = GOOL_InterpretObject(arg0, 3, 0);
        if (i >= -0xFE) {
            return i;
        }
    }
    return -0xFF;
}

