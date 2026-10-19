#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Initialise SPU state and its 24 cached voice values. */

s32 ResetCallback(void);
void _spu_init(s32);
void _spu_FsetRXX(s32, u32, s32);
void SpuStart(u32);



/* Partial memory view: element zero precedes the 24 cached voice values. */


void _SpuInit(s32 arg0) {
    u32 level;
    u16 *voice;
    s32 remaining;

    ResetCallback();
    _spu_init(arg0);
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
    SpuStart(level);
    D_80055950 = 0;
    D_80055954 = 0;
    g_spu_rev_param = 0;
    D_80055964 = 0;
    D_80055966 = 0;
    D_80055968 = 0;
    D_8005596C = 0;
    D_80055958 = D_80055DAC[0];
    _spu_FsetRXX(0xD1, D_80055DAC[0], 0);
    D_8005594C = 0;
    D_800558FC = 0;
    D_800559A4 = 0;
}
