asm(
	".section h0; .set h0,0xD96620; .string \"%s expected but got %s\\0\\0\";"  // from `"attempt to %s a %s value",
	".section h1; .set h1,0xD95BD0; .string \"userdata\\0\\0\\0\\0\\0\\0\\0\";" // from `"use as userdata"`
	".section h2; .set h2,0xE4F948; .string \"string\\0\\0\\0\\0\\0\\0\\0\";"   // from `"use as string"`
	".section h3; .set h3,0xE4F958; .string \"boolean\\0\\0\\0\\0\\0\\0\\0\";"  // from `"use as boolean"`
	".section h4; .set h4,0xE4FFC8; .string \"integer\\0\\0\\0\\0\\0\\0\\0\";"  // from `"use as integer"`
	".section h5; .set h5,0xE58F28; .string \"thread\\0\\0\\0\\0\\0\\0\\0\";"   // from `"use as thread"`
	".section h6; .set h6,0xE59668; .string \"number\\0\\0\\0\\0\\0\\0\\0\";"   // from `"use as number"`
);
