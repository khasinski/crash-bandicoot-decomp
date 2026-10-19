#include "common.h"
/* GCC_VERSION: 2.6.3 */


u8 CdStatus(void) {
    return g_cd_read_sectors;
}
