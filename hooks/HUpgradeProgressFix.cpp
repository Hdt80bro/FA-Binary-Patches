#include "../define.h"
asm(
  ".section h0; .set h0,0x5F5C21;"
  "JMP "QU(UpgradeProgressFix)";"
);
