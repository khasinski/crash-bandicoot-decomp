/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 0 */
#include "common.h"
typedef struct {u8 bytes[4];} BufferToken;
extern BufferToken g_pbak_seed_val;
extern BufferToken g_pbak_frame_cursor[];
void *Gpu_RoundTicks(void) {
BufferToken *base=g_pbak_frame_cursor;
 (void)frame_counter;
 *(base-2)=g_pbak_seed_val; return base-2;
}
