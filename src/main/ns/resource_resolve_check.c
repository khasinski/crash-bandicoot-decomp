/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
#include "common.h"
s32 func_80014C08();
s32 func_80015A3C(s32 *handle) {
    s32 initial=handle[0];
    s32 resolved;
    if (!(initial&1)) return initial;
    func_80014C08(initial,handle[1]);
    resolved=handle[0];
    if (!(resolved&1)) return resolved;
    return -10;
}
