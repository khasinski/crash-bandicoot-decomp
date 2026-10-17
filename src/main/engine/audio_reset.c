/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
/* GNU_AS_G: 8 */
#include "common.h"
#include "audio_channels.h"

typedef struct {
    u32 mask;
    s16 volume_left, volume_right;
    s16 mode_left, mode_right;
    u8 pad0C[4];
    u16 cd_left, cd_right;
    s32 cd_mix, cd_reverb;
    u16 external_left, external_right;
    s32 external_mix, external_reverb;
} SpuCommonAttributes;

typedef struct {
    s32 unk00;
    u32 b0 : 1;
    u32 b1 : 1;
    u32 b2 : 1;
    u32 b3 : 1;
    u32 b4 : 1;
    u32 b5 : 1;
    u32 b6 : 1;
    u32 b7 : 1;
    u32 b8 : 1;
    u32 b9 : 1;
    u32 b10 : 1;
    u32 b11 : 1;
    s32 unk08;
    void *unk0C;
    u8 unk10;
    u8 unk11;
    u16 unk12;
    u16 unk14;
    u16 unk16;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    u8 pad24[0x20];
} VoiceEntry;

extern VoiceEntry D_80056804[];
extern VoiceEntry D_80056E78;
extern u8 D_80056EE4[];
extern u8 D_80056670[];
extern s32 D_80056710[];
extern s32 D_80061914[];
extern s16 D_80056660;
extern s16 D_80056664;
extern s32 D_8005666C;

void func_800497F4(void);
void func_8004C990(void *, s16, s16);
s32 func_80045D70(s32, void *);
void func_80048B30(SpuCommonAttributes *);
void func_80048A54(s32);
s32 func_80030008(s32, s16, s16, s32, s32);
void func_8002FFFC(s16);
void func_8004B7D8(s16, s16);

void func_8002FDE0(void) {
    s32 i;
    SpuCommonAttributes attr;

    for (i = 0; i < 24; i++) {
        D_80056804[i].b3 = 0;
    }
    func_800497F4();
    func_8004C990(D_80056EE4, 1, 2);
    func_80045D70(0, D_80056670);
    attr.mask = 3;
    attr.volume_left = 0x3FFF;
    attr.volume_right = 0x3FFF;
    func_80048B30(&attr);
    func_80048A54(0);
    D_80056E78.unk0C = NULL;
    D_80056E78.unk10 = 1;
    D_80056E78.unk11 = 0x80;
    D_80056E78.unk12 = 0x3FFF;
    D_80056E78.unk14 = 0;
    D_80056E78.unk16 = 0x1000;
    D_80056E78.unk18 = 0;
    D_80056E78.unk1C = 0;
    D_80056E78.unk20 = 0;
    D_80056E78.b1 = 0;
    D_80056E78.b0 = 0;
    D_80056E78.b2 = 0;
    D_80056E78.b3 = 0;
    D_80056E78.b4 = 0;
    D_80056E78.b5 = 0;
    D_80056E78.b6 = 0;
    D_80056E78.b7 = 0;
    D_80056E78.b8 = 0;
    D_80056E78.b9 = 1;
    D_80056E78.b10 = 1;
    D_80056E78.b11 = 0;
    switch (D_80056710[0]) {
    case 0x5:
    case 0x1C:
    case 0x1D:
    case 0x34:
        func_80030008(5, 0x2000, 0x2000, 0, 0);
        break;
    case 0x25:
        func_80030008(3, 0x2000, 0x2000, 0, 0);
        break;
    }
    func_8002FFFC((D_80061914[0] * 0x3FFF) >> 8);
    D_80056660 = 0x3FFF;
    D_80056664 = 0;
    func_8004B7D8(0x7F, 0x7F);
    D_8005666C = 0;
}
