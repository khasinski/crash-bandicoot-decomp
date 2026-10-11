/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
#include "common.h"
void *func_8001BA90(u8 *object,s32 state) {
    if (*(s32 *)(object+0xD8)==state) return object;
    return 0;
}
