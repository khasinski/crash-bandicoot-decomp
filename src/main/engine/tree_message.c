/* GCC_VERSION: 2.6.3 */
#include "object_links.h"
s32 func_80024CC8(Node *, void *);
extern u8 D_80060DB8[];
s32 func_80025134(Node *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    struct { Node *sender; s32 word04, word08, word0C, word10, word14; } message;
    void *context = &message;
    s32 index = 0;
    u8 *root = D_80060DB8;
    message.sender = arg0;
    message.word04 = arg1;
    message.word08 = arg3;
    message.word0C = arg2;
    message.word10 = 0;
    message.word14 = arg4;
    do {
        func_8001B92C((Node *)root, &func_80024CC8, context);
        index++;
        root += 8;
    } while (index < 8);
    return -0xFF;
}
