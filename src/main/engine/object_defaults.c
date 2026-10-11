#include "gool.h"
#include "resource.h"

/* GCC_VERSION: 2.6.3 */
typedef GoolDefaults Defaults;
typedef ResourceEntry Entry;
typedef GoolDefaultsObject Object;
/* Export the real small-common storage emitted locally by maspsx. */
asm(".globl D_800566B4");
Object *D_800566B4;
void func_8001EA00(Object *object,s32 mode) {
    Entry *entry;
    Defaults *defaults;
    entry=object->entry;
    if(entry==0) entry=D_80057914;
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
