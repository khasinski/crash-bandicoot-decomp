#include "common.h"


/* Call the registered callback on alternate invocations. */
void _SsSeqCalledTbyT_1per2(void) {
    if (D_8005626C == 0) {
        D_8005626C = 1;
        return;
    }
    D_8005626C = 0;
    D_80056260();
}
