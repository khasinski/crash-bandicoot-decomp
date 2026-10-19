#ifdef CRASH_EXT_GOOL_ALLOC
extern void *g_player;
extern s32 *g_ns_page_pool;
#endif

#ifdef CRASH_EXT_GOOL_BROADCAST_0
extern LevelDesc *g_ns_page_pool[];
#endif

#ifdef CRASH_EXT_GOOL_BROADCAST_1
extern s32 g_fade_counter[];
extern u8 g_pbak_header_byte_0[];
extern u32 g_pbak_frame_cursor[];
#endif

#ifdef CRASH_EXT_GOOL_CHANGE_STATE_0
extern struct {
    u8 reserved[0x10];
    u8 *data;
} *g_pads;
extern struct {
    s32 word_0;
    s32 type;
} *g_ns_page_pool;
extern void *gp_crash_obj;
extern void *g_savestate[2];
#endif

#ifdef CRASH_EXT_GOOL_CHANGE_STATE_1
extern struct {
    u8 reserved[0x7C];
    u32 stamp;
} *g_db_prev[2];
#endif

#ifdef CRASH_EXT_GOOL_CHANGE_STATE_2
extern GoolUpdateGlobals gool_update;
#endif

#ifdef CRASH_EXT_GOOL_CREATE_OBJECT_0
extern NsdTable *g_ns_page_pool[];
extern GoolObj *g_player[];
extern ResourceEntry *g_pads[];
extern GoolObj g_gool_obj_list_3;
extern GoolObj *gp_crash_obj;
extern GoolObj g_gool_obj_list_7;
#endif

#ifdef CRASH_EXT_GOOL_CREATE_OBJECT_1
extern ZoneEntity *g_mdat_title_str_ptr[];
extern GoolObj g_gool_obj_list_4;
#endif

#ifdef CRASH_EXT_GOOL_ENTRIES_9D08
extern u16 *gp_level_entry;
extern struct {
    u8 reserved[0x10];
    u8 *data;
} *g_pads;
extern s32 g_view_proj;
extern struct {
    s32 word_0;
    s32 type;
} *g_ns_page_pool;
#endif

#ifdef CRASH_EXT_GOOL_ENTRIES_A2F4
extern struct {
    u8 reserved[0x10];
    ZoneFogHeader *data;
} *g_pads;
extern struct {
    s32 word_0;
    s32 type;
} *g_ns_page_pool;
#endif

#ifdef CRASH_EXT_GOOL_ENTRIES_A3CC
extern u16 *gp_level_entry[];
extern ZoneHeader *g_pads[];
extern s32 g_view_proj[];
extern NsdHeader *g_ns_page_pool[];
#endif

#ifdef CRASH_EXT_GOOL_ENTRIES_A5E0
extern u16 *gp_level_entry[];
extern struct {
    u8 reserved[0x10];
    u8 *data;
} *g_pads[];
#endif

#ifdef CRASH_EXT_GOOL_ENTRIES_A8CC
extern u16 *gp_level_entry[];
extern ZoneHeader *g_pads[];
extern s32 g_view_proj[];
extern NsdHeader *g_ns_page_pool[];
#endif

#ifdef CRASH_EXT_GOOL_ENTRIES_AAE0_0
extern u16 *gp_level_entry[];
extern struct {
    u8 reserved[0x10];
    u8 *data;
} *g_pads[];
extern void * gp_crash_obj;
#endif

#ifdef CRASH_EXT_GOOL_ENTRIES_AAE0_1
extern GoolAllocGlobals gool_alloc;
extern GoolObj * volatile g_player[];
extern s32 g_gool_obj_list_7[];
extern void *g_savestate[];
#endif

#ifdef CRASH_EXT_GOOL_INTERPRET
extern GoolObj *gp_crash_obj;
extern ResourceEntry *g_pads[];
extern ResourceEntry *g_cur_zone_ptr[];
extern PadStateView *g_db_cur[];
extern LevelStateView *g_ns_page_pool[];
extern GoolObj g_gool_obj_list_4;
#endif

#ifdef CRASH_EXT_GOOL_OBJECT_RELEASE_CALLBACK
extern s32 g_cur_zone_ptr;
#endif

#ifdef CRASH_EXT_GOOL_PATH_FOLLOW
extern GoolVec3 g_path_orient_zero_vec;
extern Unk4Bytes gp_path_orient_step;
#endif

#ifdef CRASH_EXT_GOOL_PHYSICS_0
extern ResourceEntry *g_pads[];
#endif

#ifdef CRASH_EXT_GOOL_PHYSICS_1
extern GoolObj * gp_crash_obj;
#endif

#ifdef CRASH_EXT_GOOL_PHYSICS_2
extern GoolBoundsGlobals g_obj_bounds;
#endif

#ifdef CRASH_EXT_GOOL_PHYSICS_3
extern GoolMoveParams g_accel_states[];
extern GoolDirEntry g_move_states[];
extern s32 g_cam_dir_rot_y[];
extern GoolTimeState *g_db_cur[];
extern u8 g_solid_wall_plot_buf[];
#endif

#ifdef CRASH_EXT_GOOL_PROJECT
extern u8 g_m_wgeo_view[];
extern s32 g_cam_trans_x;
#endif

#ifdef CRASH_EXT_GOOL_QUERY_NEAREST
extern struct {
    u8 reserved[0x10];
    u8 *data;
} *g_pads;
extern struct {
    s32 word_0;
    s32 type;
} *g_ns_page_pool;
#endif

#ifdef CRASH_EXT_GOOL_RESOURCE
extern s32 g_mdat_title_str_ptr;
#endif

#ifdef CRASH_EXT_GOOL_SEND_EVENT_0
extern GoolTimeState *g_db_cur[];
#endif

#ifdef CRASH_EXT_GOOL_SEND_EVENT_1
extern GoolObjView *gp_crash_obj;
#endif

#ifdef CRASH_EXT_GOOL_UPDATE_OBJECT_0
extern ResourceEntry *g_pads[];
extern GoolObj *gp_crash_obj;
#endif

#ifdef CRASH_EXT_GOOL_UPDATE_OBJECT_1
extern GoolObj *g_savestate[];
#endif

#ifdef CRASH_EXT_GOOL_UPDATE_OBJECT_2
extern RenderProjectionState g_view_proj;
extern RenderBufferView *g_ot_cur[];
#endif

#ifdef CRASH_EXT_GOOL_VM_OPERANDS_0
extern GoolTimeState *g_db_cur[];
#endif

#ifdef CRASH_EXT_GOOL_VM_OPERANDS_1
extern GoolPad g_gool_pads[];
extern GoolDirEntry g_move_states[];
#endif
