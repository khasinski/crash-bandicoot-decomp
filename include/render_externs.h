#ifdef CRASH_EXT_RENDER_CAMERA_MATRIX_0
extern s16 g_m_rot;
extern s16 g_m_color;
extern s16 g_m_wgeo_view;
#endif

#ifdef CRASH_EXT_RENDER_CAMERA_MATRIX_1
extern Copy12 g_cam_trans_x;
extern Copy12 g_cam_dir_rot_y;
#endif

#ifdef CRASH_EXT_RENDER_CAMERA_MATRIX_2
extern CamBlock g_m_light;
#endif

#ifdef CRASH_EXT_RENDER_DISPLAY
extern u16 *gp_level_entry;
#endif

#ifdef CRASH_EXT_RENDER_FRAME_UPDATE_0
extern BufferToken g_pbak_header_byte_0[];
extern BufferToken g_pbak_seed_val;
extern u32 g_fade_counter;
extern s32 g_cam_rot_xz[];
extern struct { RenderBufferFull *buf; } g_db_cur;
extern RenderBufferFull *g_db_prev;
extern RenderBufferFull *g_ot_cur;
#endif

#ifdef CRASH_EXT_RENDER_FRAME_UPDATE_1
extern s32 *gp_cur_pbak_header;
#endif

#ifdef CRASH_EXT_RENDER_FRAME_UPDATE_2
extern ZoneEntry8214 *g_pads[];
#endif

#ifdef CRASH_EXT_RENDER_GTE
extern u8 g_m_rot[];
#endif

#ifdef CRASH_EXT_RENDER_QUAD_DRAW
extern PrimBuf9398 *g_ot_cur;
extern s32 g_view_proj;
#endif

#ifdef CRASH_EXT_RENDER_TILE_FADE
extern FadeTable g_tile_fade_alpha_table;
#endif

#ifdef CRASH_EXT_RENDER_TRANSFORM_88CC
extern u8 g_m_wgeo_view[];
extern u8 g_m_color[];
extern s32 g_view_proj[];
extern GoolObj88CC *g_shader_obj_color_scale[];
extern GoolObj88CC *gp_crash_obj[];
extern ResourceEntry88CC *g_pads[];
#endif

#ifdef CRASH_EXT_RENDER_TRANSFORM_8964
extern s32 g_view_proj[];
extern ZoneEntry8964 *g_pads[];
#endif

#ifdef CRASH_EXT_RENDER_TRI_DRAW_0
extern s32 g_view_proj;
#endif

#ifdef CRASH_EXT_RENDER_TRI_DRAW_1
extern PrimBuf9398 *g_ot_cur;
extern s32 g_view_proj;
#endif

#ifdef CRASH_EXT_RENDER_TRI_DRAW_2
extern ZoneEntry9DCC *g_pads;
extern SortList9DCC *gp_level_entry;
#endif

#ifdef CRASH_EXT_RENDER_WORLD_SETUP
extern s32 g_cam_trans_x;
extern s16 g_m_light;
extern struct {
    s32 word_0;
    s32 level_id;
} *g_ns_page_pool;
extern s32 g_island_cam_state;
#endif
