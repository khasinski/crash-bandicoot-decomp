#include "common.h"


void _SsTrapIntrVSync(void) {
    if (D_80056264 != 0) {
        D_80056264();
    }
    D_80056260();
}
