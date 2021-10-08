void GetTimeForProfile()
{
    __asm
    (
        "SUB ESP,0x8 \n"
        "PUSH ESP \n"
        "CALL DWORD PTR [0xC0F470] \n" //QueryPerformanceCounter
        "FILD QWORD PTR [ESP] \n"

        "PUSH ESP \n"
        "CALL DWORD PTR [0xC0F46C] \n" //QueryPerformanceFrequency
        "FILD QWORD PTR [ESP] \n"

        "MOV ECX,[ESI+0xC] \n"
        "FLD DWORD PTR [ECX+0x4] \n" //OriginTime
        "FMUL ST(1) \n"
        "FSUBP ST(2), ST \n"
        "FDIVP ST(1), ST \n"
        "FSTP DWORD PTR [ESP+0x4] \n"

        "MOV [ESP], ESI \n"
        "CALL 0x0090CD40\n" //PushNumber
        "ADD ESP,0x8 \n"
        "MOV EAX,0x1 \n"
    );
}