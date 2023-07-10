asm(
  ".section h0; .set h0,0x957E35;"
  "PUSH 0x3FF000;"

  ".section h1; .set h1,0x915A92;"
  "ADD EAX,EAX;"
  "JGE .+0x73;"
  "MOV EAX,DWORD PTR DS:[ESI+0x2C];"
  "ADD EAX,0x10000000;"
  "JMP .+0x69;"

  ".section h2; .set h2,0x915B05;"
  "JMP .-0x73;"
);