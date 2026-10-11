/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 0 */
#include "common.h"
typedef struct {u8 bytes[4];} BufferToken;
extern volatile u32 frame_counter __asm__("func_80034520");
extern BufferToken D_8005796C;
extern u8 D_80057970[];
void *func_80016E28(void) {
u8 *base=D_80057970;
 (void)frame_counter;
 *(BufferToken *)(base-8)=D_8005796C; return base-8;
}
