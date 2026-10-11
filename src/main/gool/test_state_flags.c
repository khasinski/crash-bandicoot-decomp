/* GCC_VERSION: 2.6.3 */
#include "common.h"
typedef struct {u8 data[0x120];u32 flags;} Object;
Object *GOOL_TestObjectStateFlags(Object *object,u32 flags) {
 if (object->flags & flags) return object;
 return NULL;
}
