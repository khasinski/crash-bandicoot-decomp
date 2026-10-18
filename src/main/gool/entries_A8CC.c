/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"

extern void func_80042E9C(void *);
extern void func_80042ECC(void *);
extern void func_80033FBC(void *, u32, s32);
extern s32 *func_80016E18(void);
extern void func_80036BF4(u16 *, s32, s32, s32, s32 *, void *, u32, s32);

typedef struct ZoneHeader {
    u8 pad[0x10];
    u8 *data;
} ZoneHeader;

typedef struct NsdHeader {
    s32 unk0;
    s32 type;
} NsdHeader;

typedef struct {
    u8 pad[0x48];
    s32 a, b, c, d, e, f, g, h;
} Sp;

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

extern s32 D_80056440;
extern s32 D_80056444;
extern s32 D_80056448;
extern s32 D_8005644C;
extern s32 D_80056450;
extern s32 D_80056454;
extern s32 D_80056458;
extern s32 D_8005645C;

void func_8001A0CC(s32 arg0)
{
    u32 sp20;
    s32 sp24;

    if (*D_800566B8[0] != 0) {
        func_80042E9C(D_800577E4);
        func_80042ECC(D_800577E4 + 0x110);
        func_80033FBC(D_80057914[0]->data + 4, 0x1F800100, 0x100);
        {
            u32 *_arg0 = &sp20;
            s32 _type;
            u32 _offset;
            u32 _val;
            s32 _flag;
            s32 _zero = 0;
            s32 _h;
            NsdHeader *_hdr;
            do { } while (0);
            if (_zero) {
                if (arg0) { _offset = 1; _zero = 1; }
                _zero = 2;
            }
            ((Sp *)0x1F800000)->a = D_80056440 << 4;
            ((Sp *)0x1F800000)->b = D_80056444 << 4;
            ((Sp *)0x1F800000)->c = D_80056448 << 4;
            ((Sp *)0x1F800000)->d = D_8005644C;
            ((Sp *)0x1F800000)->e = D_80056450 << 4;
            ((Sp *)0x1F800000)->f = D_80056454 << 4;
            ((Sp *)0x1F800000)->g = D_80056458 << 4;
            _h = D_8005645C;
            do { } while (0);
            _hdr = D_8005C53C[0];
            ((Sp *)0x1F800000)->h = _h;
            _type = _hdr->type;
            if (_type == 0x14 || _type == 0x16) {
                _offset = D_80060DF0.wordAA8 * 0xC80 + 0x64000;
                _val = (*(u32 *)(D_80057914[0]->data + 0x2E8) - _offset) >> 8;
                D_80060DF0.wordAC8 = _val + 0x7D0;
                _flag = *(s32 *)(D_80057914[0]->data + 0x2EC);
                *_arg0 = _val;
            } else {
                _val = (*(s32 *)(D_80057914[0]->data + 0x2E8) - 0x32000) >> 8;
                _flag = *(s32 *)(D_80057914[0]->data + 0x2EC);
                if (_flag == 1) {
                    _val -= 0x4B0;
                }
                D_80060DF0.wordAC8 = _val + 0x320;
                *_arg0 = _val;
            }
            *(&sp24) = _flag;
        }
        func_80036BF4(D_800566B8[0], arg0, 0x800 - (D_800578D0[0] / 2), D_80057960[0], func_80016E18(), D_80051774, sp20, sp24);
    }
}
