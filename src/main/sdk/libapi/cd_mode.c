#include "common.h"
/* GCC_VERSION: 2.6.3 */


u8 CdMode(void) {
    return g_cd_com_flags_tab[0];
}
