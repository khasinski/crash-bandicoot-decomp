/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"

static __inline__ s32 func_8001FB20(s32 value, s32 bits)
{
    s32 shift = 0x20 - bits;
    return (s32)((u32)value << shift) >> shift;
}

extern s32 * D_80056488;
extern s32 D_8005648C;
void printf(char *, ...);

typedef struct GoolExecView {
    u8 pad00[0x10];
    struct {
        s32 unk00;
        s32 unk04;
        s32 unk08;
        s32 unk0C;
        s32 unk10;
    } *header;
    u8 *code;
    s32 *data;
    u16 *states;
    u8 *unk20;
} GoolExecView;

typedef struct GoolObjView {
    u8 pad00[0x20];
    GoolExecView *exec;
    GoolExecView *external;
    u8 pad28[0x38];
    struct GoolObjView *links[8];
    u8 pad80[0x48];
    u32 status_a;
    u32 status_b;
    u32 status_c;
    u8 padD4[0x8];
    s32 *sp;
    u32 *pc;
    s32 *fp;
    u32 *unkE8;
    u32 *unkEC;
    s32 unkF0;
    s32 unkF4;
    u8 padF8[0x30];
    s32 anim_type;
    u8 pad12C[0x10];
    s32 event;
} GoolObjView;

typedef struct GoolTimeState {
    u8 pad00[0x84];
    u32 unk84;
} GoolTimeState;

extern GoolTimeState *D_80058404[];

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define SCALE_DT(x) (((s32)((x) * (D_80058404[0]->unk84 < 0x67U ? D_80058404[0]->unk84 : 0x66))) / 1024)

static __inline__ s32 *GoolRegPtr(GoolObjView *obj, u32 reg, s32 mode)
{
    if (reg == 0x1F) {
        if (mode == 0) {
            return --obj->sp;
        } else {
            return obj->sp++;
        }
    } else {
        return (s32 *)((u8 *)obj + ((reg << 2) + 0x60));
    }
}

s32 *func_8001FC4C(GoolObjView *obj, u32 gop, s32 mode)
{
    GoolObjView *link;
    u32 offset;
    GoolExecView *ptr;
    u32 idx;

    if (gop & 0x800) {
        if (gop & 0x400) {
            if (gop & 0x200) {
                return GoolRegPtr(obj, gop & 0x1FF, mode);
            } else {
                link = obj->links[(gop >> 6) & 7];
                if (link != NULL) {
                    offset = ((gop & 0x3F) << 2) + 0x60;
                    return (s32 *)(offset + (u32)link);
                }
                return NULL;
            }
        } else if (gop & 0x200) {
            if (gop & 0x100) {
                if (gop & 0x80) {
                    if (gop == 0xBE0) {
                        return NULL;
                    } else if (gop == 0xBF0) {
                        return (s32 *)1;
                    } else if (0) {
                        printf("");
                    }
                } else {
                    return &obj->fp[func_8001FB20(gop, 7)];
                }
            } else {
                ptr = (GoolExecView *)&D_80056488[D_8005648C = !D_8005648C];
                *(s32 *)ptr = func_8001FB20(gop, 8) << 4;
                return (s32 *)ptr;
            }
        } else {
            ptr = (GoolExecView *)&D_80056488[D_8005648C = !D_8005648C];
            *(s32 *)ptr = func_8001FB20(gop, 9) << 8;
            return (s32 *)ptr;
        }
    } else {
        idx = gop & 0x3FF;
        if (gop & 0x400) {
            ptr = obj->external;
        } else {
            ptr = obj->exec;
        }
        return (s32 *)((idx <<= 2) + (u32)(ptr = (GoolExecView *)ptr->data));
    }
}

typedef struct GoolPad {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
    u32 unk10;
} GoolPad;

typedef struct GoolDirEntry {
    s32 dir;
    s32 angle;
    s32 speed_scale;
} GoolDirEntry;

extern GoolPad D_8005E71C[];
extern GoolDirEntry D_80052B64[];

s32 func_8001FDC4(u32 arg0, s32 port)
{
    u32 res;
    s32 dir_test;

    res = 1;
    switch ((arg0 >> 12) & 3) {
    case 1:
        res = D_8005E71C[port].unk0 & (arg0 & 0xFFF);
        break;
    case 2:
        res = D_8005E71C[port].unk4 & (arg0 & 0xFFF);
        break;
    case 4:
        dir_test = arg0 & 0xFFF;
        res = dir_test & (D_8005E71C[port].unk4 | D_8005E71C[port].unk8);
        break;
    case 3:
        dir_test = arg0 & 0xFFF;
        res = dir_test & (D_8005E71C[port].unk0 | D_8005E71C[port].unkC);
        break;
    }
    if (res == 0) {
        return (arg0 >> 20) & 1;
    }
    dir_test = (arg0 >> 16) & 0xF;
    switch ((arg0 >> 14) & 3) {
    case 1:
        switch (dir_test) {
        case 9:
            res = D_8005E71C[port].unk0 & 0x1000;
            break;
        case 10:
            res = D_8005E71C[port].unk0 & 0x2000;
            break;
        case 11:
            res = D_8005E71C[port].unk0 & 0x4000;
            break;
        case 12:
            res = D_8005E71C[port].unk0 & 0x8000;
            break;
        default:
            res = (dir_test == D_80052B64[(D_8005E71C[port].unk4 & 0xF000) >> 12].dir)
               && (dir_test != D_80052B64[(D_8005E71C[port].unk8 & 0xF000) >> 12].dir);
            break;
        }
        break;
    case 2:
        switch (dir_test) {
        case 9:
            res = D_8005E71C[port].unk4 & 0x1000;
            break;
        case 10:
            res = D_8005E71C[port].unk4 & 0x2000;
            break;
        case 11:
            res = D_8005E71C[port].unk4 & 0x4000;
            break;
        case 12:
            res = D_8005E71C[port].unk4 & 0x8000;
            break;
        default:
            res = (dir_test == D_80052B64[(D_8005E71C[port].unk4 & 0xF000) >> 12].dir);
            break;
        }
        break;
    case 3:
    case 4:
        res = ((dir_test = (arg0 >> 16) & 0xF) == D_80052B64[(D_8005E71C[port].unk4 & 0xF000) >> 12].dir)
           || (dir_test == D_80052B64[(D_8005E71C[port].unk8 & 0xF000) >> 12].dir);
        break;
    }
    dir_test = res;
    if (arg0 & 0x100000) {
        dir_test = !dir_test;
    }
    return dir_test;
}
