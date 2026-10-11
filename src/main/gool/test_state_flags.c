/* GCC_VERSION: 2.6.3 */
#include "gool.h"
typedef GoolRuntimeObject Object;
Object *GOOL_TestObjectStateFlags(Object *object,u32 flags) {
 if (object->flags120 & flags) return object;
 return NULL;
}
