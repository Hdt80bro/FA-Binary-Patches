void SimArmyCreate()
{
    asm
    (
        "SUB ECX,ESI\n"
        "PUSH ECX;"
        "PUSH EAX;"
        "PUSHAD;"
        "MOV ESI,0;"
        "MOV EBX,0;"
    "L1: PUSH EAX;"
        "MOV EAX,0x0A;"
        "MUL BX;"
        "MOV EBX,EAX;"
        "POP EAX;"
        "MOV EDX,DS:[ESI+EAX];"
        "SUB EDX,0x30;"
        "ADD BL,DL;"
        "INC ESI;"
        "LOOP SHORT L1;"
        "MOV EAX,0x258;"
        "MUL BX;"
        "MOV SS:[EBP+0x1CC],EAX;"
        "POPAD;"
        "LEA ECX,SS:[ESP+0x70];"
        "JMP 0x006FF3D6;"
    );
}