#include "common.h"

/* GCC_VERSION: 2.6.3 */

/* Forward the CD controller request with its original arguments. */

void CdFlush(void) {
    CD_initvol();
}
