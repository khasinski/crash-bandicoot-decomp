/* GCC_VERSION: 2.6.3 */
#include "gool.h"
#include "resource.h"
extern s32 g_draw_stamp;
/* Only the cache word at +0x7C is established by this routine. */
typedef struct LevelCacheView {
    u8 pad00[0x7C];
    u32 word7C;
} LevelCacheView;

ResourceEntry *Ns_Open(s32 *, s32, s32);
void GOOL_CreateObject(void *, s32, s32, s32, s32 *, s32);
void Level_Restart(void *);
void Math_Sranda(s32);
extern u8 *gp_cur_pbak_header;
extern GoolActorView *gp_crash_obj;
extern LevelResourceView *gp_cur_pbak_frame;
extern LevelCacheView *g_db_prev;
extern s32 g_ns_load_done_flag;

extern s32 g_checkpoint_id_2;

__inline__ void Pbak_Start(void)
{
    GoolActorView *object;

    g_pbak_frame_step = 2;
    gp_cur_pbak_header = gp_cur_pbak_frame->bytes52C;
    Math_Sranda(gp_cur_pbak_frame->word04);
    object = gp_crash_obj;
    g_draw_stamp = gp_cur_pbak_frame->word0C;
    __builtin_memcpy(&g_db_prev->word7C, &gp_cur_pbak_frame->word50C,
                     sizeof(g_db_prev->word7C));
    __builtin_memcpy(object->bounds, gp_cur_pbak_frame->bounds, sizeof(object->bounds));
    g_checkpoint_id_2 = -1;
    Level_Restart(gp_cur_pbak_frame->bytes10);
}

void Pbak_Play(s32 *resource_id)
{
    s32 arguments[2];
    ResourceEntry *entry;

    g_ns_load_done_flag = 0;
    entry = Ns_Open(resource_id, 1, 1);
    *resource_id = 0x6396347F;
    gp_cur_pbak_frame = (LevelResourceView *)entry->data;
    arguments[0] = 0x8E7;
    arguments[1] = 0x4E19;
    GOOL_CreateObject(g_handles, 4, 8, 2, arguments, 1);
    Pbak_Start();
}
