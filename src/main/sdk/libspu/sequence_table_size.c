/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

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
    s16 field_78;
    s16 field_7A;
    u8 pad7C[0x14];
    s32 field_90;
    s32 field_94;
    s32 field_98;
    s32 field_9C;
    s32 field_A0;
    s32 field_A4;
    u8 padA8[4];
} SequenceState;

extern SequenceState *D_80060418[];
extern s16 D_80060C98;
extern s16 D_80060CA0;

void func_8004C990(void *table, s16 s_max, s16 t_max) {
    s32 i;
    s32 j;

    D_80060C98 = s_max;
    D_80060CA0 = t_max;
    for (i = 0; i < s_max; i++) {
        D_80060418[i] = (SequenceState *)table + i * t_max;
    }
    for (i = 0; i < D_80060C98; i++) {
        for (j = 0; j < D_80060CA0; j++) {
            D_80060418[i][j].field_90 = 0;
            D_80060418[i][j].field_3C = 0xFF;
            D_80060418[i][j].field_0 = 0;
            D_80060418[i][j].field_3E = 0;
            D_80060418[i][j].field_40 = 0;
            D_80060418[i][j].field_94 = 0;
            D_80060418[i][j].field_98 = 0;
            D_80060418[i][j].field_42 = 0;
            D_80060418[i][j].field_A4 = 0;
            D_80060418[i][j].field_A0 = 0;
            D_80060418[i][j].field_9C = 0;
            D_80060418[i][j].field_44 = 0;
            D_80060418[i][j].field_74 = 0x7F;
            D_80060418[i][j].field_76 = 0x7F;
            D_80060418[i][j].field_78 = 0x7F;
            D_80060418[i][j].field_7A = 0x7F;
        }
    }
}
