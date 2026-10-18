/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
#include "common.h"
typedef struct {
    u8 pad00[0xD8];
    s32 pid_flags;
} GoolObj;
void *func_8001BA90(GoolObj *object,s32 state) {
    if (object->pid_flags==state) return object;
    return 0;
}
