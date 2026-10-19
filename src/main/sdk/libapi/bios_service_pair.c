/* GCC_VERSION: 2.6.3 */
/* GCC_CPU: 3000 */
#include "common.h"
s32 _card_read();
s32 _new_card(s32,s32,s32);
s32 _card_clear(s32 argument) {
    _card_read(argument);
    return _new_card(argument,0x3F,0);
}
