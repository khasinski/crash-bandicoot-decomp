/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

void func_8004F998(s16, s16, s16, s32);
void func_80050060(s16);

typedef struct {
    u8 field_0;
    u8 pad1[0x3B];
    u8 field_3C;
    u8 pad3D;
    s16 field_3E;
    s16 field_40;
    s16 field_42;
    s16 field_44;
    u8 pad46[0x2E];
    s16 field_74;
    s16 field_76;
    u8 pad78[0x18];
    s32 field_90;
    s32 field_94;
    s32 field_98;
    s32 field_9C;
    s32 field_A0;
    s32 field_A4;
    u8 padA8[4];
} SequenceState;

extern s32 D_8005E548;
extern SequenceState *D_80060418[];
extern s16 D_80060CA0;

void func_80049268(s16 arg0) {
    s32 i;

    func_8004F998(arg0, 0, 0, 1);
    func_80050060(arg0);
    D_8005E548 &= ~(1 << arg0);
    for (i = 0; i < D_80060CA0; i++) {
        D_80060418[arg0][i].field_90 = 0;
        D_80060418[arg0][i].field_3C = 0xFF;
        D_80060418[arg0][i].field_0 = 0;
        D_80060418[arg0][i].field_3E = 0;
        D_80060418[arg0][i].field_40 = 0;
        D_80060418[arg0][i].field_94 = 0;
        D_80060418[arg0][i].field_98 = 0;
        D_80060418[arg0][i].field_42 = 0;
        D_80060418[arg0][i].field_A4 = 0;
        D_80060418[arg0][i].field_A0 = 0;
        D_80060418[arg0][i].field_9C = 0;
        D_80060418[arg0][i].field_44 = 0;
        D_80060418[arg0][i].field_74 = 0x7F;
        D_80060418[arg0][i].field_76 = 0x7F;
    }
}

void func_800493E0(s16 arg0) {
    func_80049268(arg0);
}
