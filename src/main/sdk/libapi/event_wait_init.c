#include "common.h"

/* GCC_VERSION: 2.6.3 */
void PAD_init(s32, s32 *);                          /* extern */
void ChangeClearPAD(s32);                                 /* extern */
void ResetCallback();                                  /* extern */

void PadInit(s32 arg0) {
    g_pad_init_mode = arg0;
    g_pad_mode_state = -1;
    ResetCallback();
    PAD_init(0x20000001, &g_pad_mode_state);
    ChangeClearPAD(0);
}
