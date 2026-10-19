#include "common.h"
/* GCC_VERSION: 2.5.7 */
void _SsSndSetReplayMode(s32, s16);

void SsSepReplay(s16 arg0, s16 arg1) {
    _SsSndSetReplayMode(arg0, arg1);
}
