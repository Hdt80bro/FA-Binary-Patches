void GetTableSize()
{
    __asm__
    (
        "MOV EAX,[ESI+0xC] \n"
        "CMP EAX,[ESI+0x8] \n"
        "JAE Err \n"
        "CMP DWORD PTR [EAX],0x5 \n"
        "JNE Err \n"
        "MOV EAX,[EAX+0x4] \n"
        "XOR EBX,EBX \n"
        "MOV CL,[EAX+0x9] \n"
        "TEST CL,CL \n"
        "JZ L2 \n"
        "MOV EDX,1 \n"
        "SHL EDX,CL \n"
        "MOV ECX,[EAX+0x14] \n"
        "L3: \n"
        "CMP DWORD PTR [ECX+0x8],0x0 \n"
        "JE L4 \n"
        "ADD EBX,0x1 \n"
        "L4: \n"
        "ADD ECX,0x14 \n"
        "DEC EDX \n"
        "JNZ L3 \n"
        "L2: \n"
        "MOV EDX,[EAX+0x20] \n"
        "TEST EDX,EDX \n"
        "JZ L7 \n"
        "MOV ECX,[EAX+0x10] \n"
        "L5: \n"
        "CMP DWORD PTR [ECX],0x0 \n"
        "JE L6 \n"
        "ADD EBX,0x1 \n"
        "L6: \n"
        "ADD ECX,0x8 \n"
        "DEC EDX \n"
        "JNZ L5 \n"
        "L7: \n"
        "CVTSI2SS XMM0,EBX \n"
        "SUB ESP,0x4 \n"
        "MOVSS [ESP],XMM0 \n"
        "PUSH ESI \n"
        "CALL 0x0090CD40\n"     //PushNumber
        "ADD ESP,0x8 \n"
        "MOV EAX,0x1 \n"
        "RET \n"
        "Err: \n"
        "XOR EAX,EAX \n"
    );
}

int RegTableFuncsDesc[] = {"getsize2",
                           &GetTableSize,
                           "getn2",
                           0x00927C20,
                           0,0};

void RegTableFuncs()
{
    __asm__
    (
        "CALL 0x0090DE00 \n"
        "MOV DWORD PTR [ESP+0x8],%[RegTableFuncsDesc] \n"
        "MOV DWORD PTR [ESP+0xC],0x0 \n"
        "CALL 0x0090DE00 \n"
        "JMP 0x009283B6 \n"
        :
        : [RegTableFuncsDesc] "i" (RegTableFuncsDesc)
        :
    );
}