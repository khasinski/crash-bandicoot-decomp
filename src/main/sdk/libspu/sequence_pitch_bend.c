/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
/* ASPSX_VERSION: 2.34 */
#include "common.h"

s32 func_8004EADC(u16, u16);
s32 func_80050728(s16, s16);

extern u8 D_800572BA[];
extern u8 D_800572BE[];
extern u8 D_800572C0[];
extern u8 D_800572C2[];

extern u8 *D_8005CFE4;

extern s16 D_8005E56E;
extern s16 D_8005E572;

s16 func_8004F680(s16 voice, s16 arg1, s16 arg2, s16 arg3, u16 arg4) {
    s16 bend;
    u16 tone_idx;
    u16 note;
    u16 fine;
    s32 offset;
    s32 prod;

    bend = arg4 - 0x40;
    offset = voice * 0x34;
    if (*(s16 *)(D_800572BA + offset) == arg1) {
        if (*(s16 *)(D_800572C2 + offset) == arg2) {
            if (*(s16 *)(D_800572BE + offset) == arg3) {
                tone_idx = *(u16 *)(D_800572C0 + offset) + (D_8005E55F * 0x10);
                note = *(u16 *)(D_800572B8 + offset);
                if (bend > 0) {
                    note += (bend * D_8005CFE4[(tone_idx << 5) + 0xD]) / 0x3F;
                    fine = ((bend * D_8005CFE4[(tone_idx << 5) + 0xD]) % 0x3F) * 2;
                } else if (bend < 0) {
                    prod = bend * D_8005CFE4[(tone_idx << 5) + 0xC];
                    note = note + (prod / 64) - 1;
                    fine = ((prod % 64) * 2) + 0x7F;
                } else {
                    fine = 0;
                }
                D_8005E564 = D_800572C0[voice * 0x34];
                D_8005E572 = voice;
                *(volatile s16 *)(D_8005E58C + (voice << 4)) = func_8004EADC(note, fine);
                *(u8 *)((s32)D_800577A4 + voice) = *(volatile u8 *)((s32)D_800577A4 + voice) | 4;
                return 1;
            }
        }
    }
    return 0;
}

s32 func_8004F8AC(s16 arg0, s16 arg1, s16 arg2, u16 arg3) {
    s16 i;
    s32 count = 0;

    func_80050728(arg1, arg2);
    D_8005E56E = arg0;
    for (i = 0; i < D_8005E340; i++) {
        count += func_8004F680(i, arg0, arg1, arg2, arg3);
    }
    return count;
}
