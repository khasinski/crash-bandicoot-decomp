/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

typedef struct {
    u16 unk0;
    u16 unk2;
    u8 pad4[2];
    u16 unk6;
    u8 pad8[16];
    s16 unk18;
    u8 pad1A;
    u8 unk1B;
    u8 pad1C[24];
} VoiceStruct;

typedef struct { u16 value; u8 pad[50]; } VoiceU16;
typedef struct { s16 value; u8 pad[50]; } VoiceS16;
typedef struct { u8 value; u8 pad[51]; } VoiceU8;

typedef struct {
    u8 unk0[7];
    u8 unk7;
    u8 unk8[4];
    u8 unkC;
    u8 unkD[2];
    u8 unkF;
    u8 unk10[8];
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
} SvmCur;

extern SvmCur D_8005E558;
extern u8 D_8005E340;
extern VoiceStruct D_800572AC[];
extern VoiceU16 D_800572AE[];
extern VoiceU16 D_800572B2[];
extern VoiceS16 D_800572C4[];
extern VoiceU8 D_800572C7[];
void func_8004DA78(s32, s32);

u8 func_8004E59C(void)
{
    u8 var_s0;
    u16 var_t3;
    u8 var_t2;
    u16 var_t0;
    u16 var_t4;
    u8 var_t1;
    u8 var_a3;

    var_s0 = 0x63;
    var_t3 = 0xFFFF;
    var_t2 = 0;
    var_t0 = 0;
    var_t4 = D_8005E558.unkF;
    var_t1 = 0x63;
    for (var_a3 = 0; var_a3 < D_8005E340; var_a3++) {
        if ((D_800572C7[var_a3].value == 0) && (D_800572B2[var_a3].value == 0)) {
            var_s0 = var_a3;
            break;
        }
        if (D_800572C4[var_a3].value < var_t4) {
            var_t4 = D_800572C4[var_a3].value;
            var_t3 = D_800572B2[var_a3].value;
            var_t0 = D_800572AE[var_a3].value;
            var_t1 = var_a3;
            var_t2 = 1;
        } else if (D_800572C4[var_a3].value == var_t4) {
            var_t2 += 1;
            if (D_800572B2[var_a3].value < var_t3) {
                var_t3 = D_800572B2[var_a3].value;
                var_t0 = D_800572AE[var_a3].value;
                var_t1 = var_a3;
            } else if (D_800572B2[var_a3].value == var_t3) {
                if (var_t0 < (s16)D_800572AE[var_a3].value) {
                    var_t0 = D_800572AE[var_a3].value;
                    var_t1 = var_a3;
                }
            }
        }
    }
    if (var_s0 == 0x63) {
        var_s0 = var_t1;
        if (var_t2 == 0) {
            var_s0 = D_8005E340;
        }
    }
    if (var_s0 < D_8005E340) {
        for (var_a3 = 0; var_a3 < D_8005E340; var_a3++) {
            (D_800572AC + var_a3)->unk2 = D_800572AE[var_a3].value + 1;
        }
        D_800572AE[var_s0].value = 0;
        D_800572C4[var_s0].value = D_8005E558.unkF;
        if (D_800572C7[var_s0].value == 2) {
            func_8004DA78(0, 0xFFFFFF);
        }
    }
    return var_s0;
}
