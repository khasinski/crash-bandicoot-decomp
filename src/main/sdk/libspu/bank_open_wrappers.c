/* GCC_VERSION: 2.5.7 */
/* GCC_CPU: r4000 */
#include "common.h"
s32 func_80050D60(void *,s32,s32,void *);
s16 func_80050CD0(void *data,s16 bank) {return (s16)func_80050D60(data,bank,0,0);}
s16 func_80050D00(void *data,s16 bank,void *buffer) {return (s16)func_80050D60(data,bank,1,buffer);}
s16 func_80050D30(void *data,s16 bank,void *buffer) {return (s16)func_80050D60(data,bank,1,buffer);}
