#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Initialise SPU state and its 24 cached voice values. */

s32 func_8003E6F4(void);
void func_80045E50(s32);
void func_80046DB8(s32, u32, s32);
void func_80047078(u32);
extern s32 D_800558FC;
extern s32 D_8005594C;
extern s32 D_80055950;
extern s32 D_80055954;
extern s32 D_80055958;
extern s32 D_80055960;
extern s16 D_80055964;
extern s16 D_80055966;
extern s32 D_80055968;
extern s32 D_8005596C;
/* Partial memory view: element zero precedes the 24 cached voice values. */
extern u16 D_8005596E[25];
extern u32 D_800559A4;
extern s32 D_80055DAC;

void func_80046FB0(s32 arg0) {
    u32 level;
    u16 *voice;
    s32 remaining;

    func_8003E6F4();
    func_80045E50(arg0);
    level = 0xC000;
    if (arg0 == 0) {
        remaining = 0x17;
        voice = &D_8005596E[24];
        do {
            *voice = level;
            remaining -= 1;
            voice--;
        } while (remaining >= 0);
    }
    func_80047078(level);
    D_80055950 = 0;
    D_80055954 = 0;
    D_80055960 = 0;
    D_80055964 = 0;
    D_80055966 = 0;
    D_80055968 = 0;
    D_8005596C = 0;
    D_80055958 = D_80055DAC;
    func_80046DB8(0xD1, D_80055DAC, 0);
    D_8005594C = 0;
    D_800558FC = 0;
    D_800559A4 = 0;
}
