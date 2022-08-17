asm(
    ".section h0;"
    ".set h0,0x9459B0; .string \"%s expected but got %s\0\0\";" // from `"attempt to %s a %s value",
    ".set h0,0x944F60; .string \"userdata\0\0\0\0\0\0\0\";"     // from `"use as userdata"`
    ".set h0,0xA00AD0; .string \"string\0\0\0\0\0\0\0\";"       // from `"use as string"`
    ".set h0,0xA00AE0; .string \"boolean\0\0\0\0\0\0\0\";"      // from `"use as boolean"`
    ".set h0,0xA01168; .string \"integer\0\0\0\0\0\0\0\";"      // from `"use as integer"`
    ".set h0,0xA09310; .string \"thread\0\0\0\0\0\0\0\";"       // from `"use as thread"`
    ".set h0,0xA09A50; .string \"string\0\0\0\0\0\0\0\";"       // from `"use as number"`
);
