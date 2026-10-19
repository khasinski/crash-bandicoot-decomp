#include "common.h"

void _SsStart(s32);

void SsStart(void) {
    _SsStart(1);
}

void SsStart2(void) {
    _SsStart(0);
}
