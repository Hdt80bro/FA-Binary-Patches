asm(R"(
.section h0; .set h0,0x06C8B48
    #test    [eax+180h], ecx   # test toggle caps
    test    [eax+17Ch], ecx    # test command caps
)");