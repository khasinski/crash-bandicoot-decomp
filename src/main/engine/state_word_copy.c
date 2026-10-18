/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 0 */
#include "common.h"
typedef struct {u8 bytes[4];} BufferToken;
extern volatile u32 frame_counter;
extern BufferToken D_8005796C;
extern BufferToken D_80057970[];
void *func_80016E28(void) {
BufferToken *base=D_80057970;
 (void)frame_counter;
 *(base-2)=D_8005796C; return base-2;
}
