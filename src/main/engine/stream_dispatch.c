#include "common.h"

/* GCC_VERSION: 2.6.3 */
typedef struct {u16 size,flags;u8 data[1];} Stream;
extern void func_800334A0(Stream *,Stream *,Stream *);
extern void func_80033878(Stream *,Stream *,Stream *);
extern void func_80033FBC(void *,void *,s32);
Stream *func_80029B0C(Stream *source,Stream *reference,Stream *destination,s32 mode) {
    if(!(source->flags&1)) {
        func_80033FBC(source->data,destination->data,source->size);
        destination->size=source->size;
        return destination;
    }
    if(mode!=0) {
        func_800334A0(source,reference,destination);
    } else {
        func_80033878(source,reference,destination);
    }
    return destination;
}
