/* GCC_VERSION: 2.6.3 */
/* GNU_AS_G: 8 */
#include "common.h"
extern s16 D_80056EBC[];

/* Wait for a pending fade, then request the selected sequence. Tagged
 * references contain an ID; resolved references point to a handle whose
 * second word is the ID. The fourth fade argument is retained as observed
 * at this call site, although the current callee consumes three words. */
void func_800314C4();
void func_80049614();

extern s32 *D_800564FC;
extern u16 D_80056648;

void func_800317F8(s32 *reference) {
 s16 countdown;
 s32 key,ready,state;
 if(D_800566C0!=0) {
  if(D_800566C0==4 && (D_800564F8==0 || (countdown=D_800564F8-1,D_800564F8=countdown,countdown==0)))D_800566C0=1;
  state=D_800566C0;
  if(state==3) {
   key=*reference;
   if(key&1) {
    if(D_80056650!=key)goto change;
    goto finish;
   }
   if(D_80056650!=((s32 *)key)[1]) {
change:
    if(D_8005666C==0 && D_80056658!=-1 && D_800564FC==0) {
     func_80049614(D_80056654,D_80056EBC[0],(s32)(D_80056648<<16)>>23,30);
     D_800564F8=30;D_800564FC=reference;D_800566C0=4;return;
    }
   }
   state=D_800566C0;
  }
finish:
  ready=state<3;
  if(ready && state>0)func_800314C4(reference);
 }
}
