#include "gool.h"
#include "resource.h"

/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
typedef GoolDefaults Defaults;
typedef ResourceEntry Entry;
typedef GoolDefaultsObject Object;
/* Storage is owned by engine/state; retain the absolute view of the
 * resource selection word while sized D_800566B4 uses the native gp load. */
extern Object *D_800566B4;
extern Entry *selected_resource[] __asm__("D_80057914");
void func_8001EA00(Object *object,s32 mode) {
    Entry *entry;
    Defaults *defaults;
    entry=object->entry;
    if(entry==0) entry=selected_resource[0];
    if(object==D_800566B4) defaults=(Defaults *)(entry->data+0x348);
    else defaults=(Defaults *)(entry->data+0x318);
    switch(mode) {
    case 0: object->defaults=*defaults;return;
    case 1:
        object->defaults.field2A=defaults->field2A;
        object->defaults.field2C=defaults->field2C;
        object->defaults.field2E=defaults->field2E;
        return;
    }
}
