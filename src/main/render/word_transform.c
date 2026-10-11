#include "common.h"

/* GCC_VERSION: 2.6.3 */
typedef struct {
    u16 word00;
    u16 word02;
    u16 word04;
    s16 word06;
    s16 word08;
    s16 word0A;
    u16 word0C;
    u16 word0E;
    u16 word10;
} TransformWords;
void func_80017968(TransformWords *arg0, TransformWords *arg1) {
    arg0->word00 = (u16) arg1->word00;
    arg0->word02 = (u16) arg1->word02;
    arg0->word04 = (u16) arg1->word04;
    arg0->word06 = (s16) ((s32) -(arg1->word06 * 5) >> 3);
    arg0->word08 = (s16) ((s32) -(arg1->word08 * 5) >> 3);
    arg0->word0A = (s16) ((s32) -(arg1->word0A * 5) >> 3);
    arg0->word0C = (s16) -(s16) arg1->word0C;
    arg0->word0E = (s16) -(s16) arg1->word0E;
    arg0->word10 = (s16) -(s16) arg1->word10;
}
