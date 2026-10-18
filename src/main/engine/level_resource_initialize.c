/* GCC_VERSION: 2.6.3 */
#include "gool.h"
#include "resource.h"
extern s32 D_80057960;
/* Only the cache word at +0x7C is established by this routine. */
typedef struct LevelCacheView {
    u8 pad00[0x7C];
    u32 word7C;
} LevelCacheView;

ResourceEntry *func_80015118(s32 *, s32, s32);
void GOOL_CreateObject(void *, s32, s32, s32, s32 *, s32);
void func_80026650(void *);
void func_8002F76C(s32);
extern u8 *D_800566A8;
extern GoolActorView *D_800566B4;
extern LevelResourceView *D_80056704;
extern LevelCacheView *D_80058408;
extern s32 D_8005C54C;

extern s32 D_800619A0;
extern s32 D_80061A30;

__inline__ void func_8002E8CC(void)
{
    GoolActorView *object;

    D_80061A30 = 2;
    D_800566A8 = D_80056704->bytes52C;
    func_8002F76C(D_80056704->word04);
    object = D_800566B4;
    D_80057960 = D_80056704->word0C;
    __builtin_memcpy(&D_80058408->word7C, &D_80056704->word50C,
                     sizeof(D_80058408->word7C));
    __builtin_memcpy(object->bounds, D_80056704->bounds, sizeof(object->bounds));
    D_800619A0 = -1;
    func_80026650(D_80056704->bytes10);
}

void func_8002E98C(s32 *resource_id)
{
    s32 arguments[2];
    ResourceEntry *entry;

    D_8005C54C = 0;
    entry = func_80015118(resource_id, 1, 1);
    *resource_id = 0x6396347F;
    D_80056704 = (LevelResourceView *)entry->data;
    arguments[0] = 0x8E7;
    arguments[1] = 0x4E19;
    GOOL_CreateObject(D_80060DC0, 4, 8, 2, arguments, 1);
    func_8002E8CC();
}
