asm(R"(
.section h0; .set h0,0x06C8B48 #Moho::UnitTestCommandCaps_LuaFuncDef+0xD8
    #test    [eax+180h], ecx   # test toggle caps
    test    [eax+17Ch], ecx    # test command caps
)");