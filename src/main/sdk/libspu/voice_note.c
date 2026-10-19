/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"
s32 SpuVmKeyOff(s16,s16,s16,u16);
/* The retail call passes an unused mode value; allocation returns an index. */
s32 SpuVmAlloc(s32);
void SpuVmDoAllocate(void);
s32 note2pitch(void);
void vmNoiseOn(s16);
void vmNoiseOff(s32);
void SpuVmKeyOffNow(s32);
void SpuVmKeyOnNow(u8,u16);
s32 SpuVmSelectToneAndVag(u8 *,u8 *);
s32 SpuVmVSetUp(s16,s16);
typedef struct {
    u8 gap00[0x12];
    u16 programs;
} VabHeader;
extern u8 D_800572AC[];
extern u8 D_800572AE[];
extern u8 D_800572B4[];
extern u8 D_800572B6[];
extern u8 D_800572BA[];
extern u8 D_800572BE[];
extern u8 D_800572C0[];
extern u8 D_800572C2[];
extern u8 D_800572C4[];
extern u8 D_800572C7[];
extern VabHeader *D_8005CFDC;

/* Shared note context; the sample cursor points 24 bytes into it. */
extern u8 g_midi_sep[32];
s32 SpuVmKeyOn(s16 arg0, s16 arg1, s16 arg2, u16 arg3, u16 arg4, u16 arg5) {
    /* The selector writes parallel byte lists of samples and tone indices. */
    u8 sp10[128];
    u8 sp90[128];
    s16 temp_v0_3;
    s32 temp_v0_2;
    s32 var_s1;
    s32 var_s2;
    s32 var_v1;
    SequenceState *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_v0;
    u8 *temp_v1;

    var_s2 = 0;
    temp_s0 = &g_ss_score_table[arg0&255][((u32) arg0 << 0x10) >> 0x18];
    if (SpuVmVSetUp(arg1, arg2) != 0) {
        return -1;
    }
    {
        D_8005E56E = arg0;
        D_8005E55A = arg3;
        D_8005E55B = 0;
        if (arg0 == 0x21) {
            D_8005E55C = (s8) arg4;
        } else {
            D_8005E55C = (s8) ((s32) (arg4 * temp_s0->gains[temp_s0->field_12]) / 127);
        }
        g_midi_sep[5] = (s8) arg5;
        temp_v0 = (arg2 * 0x10) + D_8005CFCC;
        D_8005E562 = temp_v0[1];
        D_8005E563 = temp_v0[4];
        g_midi_sep[0] = temp_v0[0];
        if ((u8)D_8005E55F >= D_8005CFDC->programs) {
            return -1;
        }
        {
            if (arg4 == 0) {
                var_s2 = SpuVmKeyOff(arg0, arg1, arg2, arg3 & 0xFFFF);
            } else {
                temp_v0_2 = SpuVmSelectToneAndVag(sp90, sp10);
                var_s1 = 0;
                if (temp_v0_2 & 0xFF) {
                    temp_s0_2 = g_midi_sep + 0x18;
                    do {
                        var_v1 = var_s1 & 0xFF;
                        *(u16*)temp_s0_2 = (u16) sp10[var_v1];
                        temp_s0_2[-0xC] = (u8) sp90[var_v1];
                        temp_v1 = ((temp_s0_2[-0xC] + (temp_s0_2[-0x11] * 0x10)) << 5) + g_ns_vpage_pool;
                        temp_s0_2[-0x9] = (u8) temp_v1[0];
                        temp_s0_2[-0xB] = (u8) temp_v1[2];
                        temp_s0_2[-0xA] = (u8) temp_v1[3];
                        temp_s0_2[-0x8] = (u8) temp_v1[4];
                        temp_s0_2[-0x7] = (u8) temp_v1[5];
                        temp_s0_2[-0x4] = (u8) temp_v1[1];
                        temp_s0_2[-0x6] = (u8) temp_v1[6];
                        temp_s0_2[-0x5] = (u8) temp_v1[7];
                        temp_v0_3 = SpuVmAlloc(0);
                        ((s16 *)temp_s0_2)[1] = temp_v0_3;
                        if (temp_v0_3 < (s32) gp_spawn_count) {
                            *(u8*)(D_800572C7 + (temp_v0_3 * 0x34)) = 1;
                            *(s16*)(D_800572AE + (((s16 *)temp_s0_2)[1] * 0x34)) = 0;
                            *(s16*)(D_800572BA + (((s16 *)temp_s0_2)[1] * 0x34)) = arg0;
                            *(s16*)(D_800572C2 + (((s16 *)temp_s0_2)[1] * 0x34)) = (s16) temp_s0_2[-0x17];
                            *(s16*)(D_800572BC + (((s16 *)temp_s0_2)[1] * 0x34)) = (s16) temp_s0_2[-0x11];
                            *(s16*)(D_800572BE + (((s16 *)temp_s0_2)[1] * 0x34)) = arg2;
                            if (arg0 != 0x21) {
                                *(s16*)(D_800572B4 + (((s16 *)temp_s0_2)[1] * 0x34)) = arg4;
                            }
                            *(u8*)(D_800572B6 + (((s16 *)temp_s0_2)[1] * 0x34)) = (s8) arg5;
                            *(s16*)(D_800572C0 + (((s16 *)temp_s0_2)[1] * 0x34)) = (s16) temp_s0_2[-0xC];
                            *(s16*)(D_800572B8 + (((s16 *)temp_s0_2)[1] * 0x34)) = (s16) arg3;
                            *(s16*)(D_800572C4 + (((s16 *)temp_s0_2)[1] * 0x34)) = (s16) temp_s0_2[-0x9];
                            *(s16*)(D_800572AC + (((s16 *)temp_s0_2)[1] * 0x34)) = *(u16*)temp_s0_2;
                            SpuVmDoAllocate();
                            if ((s16) *(u16*)temp_s0_2 == 0xFF) {
                                vmNoiseOn(((s16 *)temp_s0_2)[1]);
                            } else {
                                SpuVmKeyOnNow(temp_v0_2 & 0xFF, note2pitch() & 0xFFFF);
                            }
                            var_s2 |= 1 << D_8005E572[0];
                        } else {
                            var_s2 = -1;
                        }
                        var_s1 += 1;
                    } while ((u32) (var_s1 & 0xFF) < (u32) (temp_v0_2 & 0xFF));
                }
            }

        }
    }
    return var_s2;
}

s32 SpuVmKeyOff(s16 arg0, s16 arg1, s16 arg2, u16 arg3) {
    u8 i;
    s32 count;
    s32 offset;

    count = 0;
    for (i = 0; i < gp_spawn_count; i++) {
        offset = i * 0x34;
        if (*(s16 *)(D_800572B8 + offset) == arg3) {
            if (*(s16 *)(D_800572BE + offset) == arg2) {
                if (*(s16 *)(D_800572BA + offset) == arg0) {
                    if (*(s16 *)(D_800572C2 + offset) == arg1) {
                        if (*(s16 *)(D_800572AC + offset) == 0xFF) {
                            vmNoiseOff(i);
                        } else {
                            D_8005E572[0] = i;
                            SpuVmKeyOffNow(0);
                        }
                        count += 1;
                    }
                }
            }
        }
    }
    return count;
}

