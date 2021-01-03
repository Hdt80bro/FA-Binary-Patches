//ROffset = 0x005283B1
#include "../preprocessor/define.h"
#include "../preprocessor/macro.h"

__asm__
(
    ".equ _funcPtr,"QU(RegTableFuncs)"-0x009283B1 \n"
);

__asm__
(   //009283B1
    "JMP _funcPtr \n"
    "ADD ESP,0x10 \n"
);