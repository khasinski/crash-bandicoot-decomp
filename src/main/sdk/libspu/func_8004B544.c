#include "common.h"
/* GCC_VERSION: 2.5.7 */
void _SsSndSetPauseMode(s16, s16);

void SsSepPause(s16 arg0, s16 arg1) {
    _SsSndSetPauseMode(arg0, arg1);
}
