asm(
	".section h0; .set h0,0xC96620L; .string \"%s expected but got %s\\0\\0\";"  // from `"attempt to %s a %s value",
	".section h1; .set h1,0xC95BD0L; .string \"userdata\\0\\0\\0\\0\\0\\0\\0\";" // from `"use as userdata"`
	".section h2; .set h2,0xD4F948L; .string \"string\\0\\0\\0\\0\\0\\0\\0\";"   // from `"use as string"`
	".section h3; .set h3,0xD4F958L; .string \"boolean\\0\\0\\0\\0\\0\\0\\0\";"  // from `"use as boolean"`
	".section h4; .set h4,0xD4FFC8L; .string \"integer\\0\\0\\0\\0\\0\\0\\0\";"  // from `"use as integer"`
	".section h5; .set h5,0xD58F28L; .string \"thread\\0\\0\\0\\0\\0\\0\\0\";"   // from `"use as thread"`
	".section h6; .set h6,0xD59668L; .string \"number\\0\\0\\0\\0\\0\\0\\0\";"   // from `"use as number"`
);
