#include "gpu.h"

/* GCC_VERSION: 2.6.3 */
typedef struct {u8 next[3];u8 length;u32 word04,word08;} Packet;
s32 func_800413AC(s16, s16);                        /* extern */
s32 func_80041478(s16, s16);                        /* extern */

void func_80040F64(Packet *arg0, GpuRect *arg1) {
    arg0->length = 2;
    arg0->word04 = func_800413AC(arg1->x, arg1->y);
    arg0->word08 = func_80041478((s16) (((u16) arg1->x + arg1->w) - 1), (s16) (((u16) arg1->y + arg1->h) - 1));
}
