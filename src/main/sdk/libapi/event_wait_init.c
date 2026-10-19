#include "common.h"

/* GCC_VERSION: 2.6.3 */
void PAD_init(s32, s32 *);                          /* extern */
void ChangeClearPAD(s32);                                 /* extern */
void ResetCallback();                                  /* extern */

void PadInit(s32 arg0) {
    D_8005E33C = arg0;
    D_80057054 = -1;
    ResetCallback();
    PAD_init(0x20000001, &D_80057054);
    ChangeClearPAD(0);
}
