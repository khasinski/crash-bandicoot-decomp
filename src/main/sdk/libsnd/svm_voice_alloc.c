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

extern SvmCur g_midi_sep;

extern VoiceStruct g_spu_vm_voice_table[];
extern VoiceU16 g_spu_vm_voice_age[];
extern VoiceU16 g_spu_vm_voice_envx[];
extern VoiceS16 g_spu_vm_voice_prior[];
extern VoiceU8 g_spu_vm_voice_auto_flag[];

s32 SpuVmAlloc(void)
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
    var_t4 = g_midi_sep.unkF;
    var_t1 = 0x63;
    for (var_a3 = 0; var_a3 < gp_spawn_count; var_a3++) {
        if ((g_spu_vm_voice_auto_flag[var_a3].value == 0) && (g_spu_vm_voice_envx[var_a3].value == 0)) {
            var_s0 = var_a3;
            break;
        }
        if (g_spu_vm_voice_prior[var_a3].value < var_t4) {
            var_t4 = g_spu_vm_voice_prior[var_a3].value;
            var_t3 = g_spu_vm_voice_envx[var_a3].value;
            var_t0 = g_spu_vm_voice_age[var_a3].value;
            var_t1 = var_a3;
            var_t2 = 1;
        } else if (g_spu_vm_voice_prior[var_a3].value == var_t4) {
            var_t2 += 1;
            if (g_spu_vm_voice_envx[var_a3].value < var_t3) {
                var_t3 = g_spu_vm_voice_envx[var_a3].value;
                var_t0 = g_spu_vm_voice_age[var_a3].value;
                var_t1 = var_a3;
            } else if (g_spu_vm_voice_envx[var_a3].value == var_t3) {
                if (var_t0 < (s16)g_spu_vm_voice_age[var_a3].value) {
                    var_t0 = g_spu_vm_voice_age[var_a3].value;
                    var_t1 = var_a3;
                }
            }
        }
    }
    if (var_s0 == 0x63) {
        var_s0 = var_t1;
        if (var_t2 == 0) {
            var_s0 = gp_spawn_count;
        }
    }
    if (var_s0 < gp_spawn_count) {
        for (var_a3 = 0; var_a3 < gp_spawn_count; var_a3++) {
            (g_spu_vm_voice_table + var_a3)->unk2 = g_spu_vm_voice_age[var_a3].value + 1;
        }
        g_spu_vm_voice_age[var_s0].value = 0;
        g_spu_vm_voice_prior[var_s0].value = g_midi_sep.unkF;
        if (g_spu_vm_voice_auto_flag[var_s0].value == 2) {
            _SpuVmSetNoiseVoice(0, 0xFFFFFF);
        }
    }
    return var_s0;
}
