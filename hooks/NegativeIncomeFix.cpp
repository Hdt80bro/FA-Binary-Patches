//HOOK ROffset = 0x003722B0

__asm
(   //007722B0
    "FSUBRP ST(1),ST \n"
    "FSTP DWORD PTR [ESP+0x24] \n"
    "MOVSS XMM1,[ESP+0x24] \n"
    "COMISS XMM2,XMM1 \n"
    "JBE .+0x0D \n" //0x007722CC
    "XORPS XMM0,XMM0 \n"
    "JMP .+0x10 \n" //0x007722D4
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
);