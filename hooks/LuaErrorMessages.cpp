// macros are generally pretty yucky, but the syntax of `asm` requires a string literal, so our instructions
// need to end up as such by compiler translation phase 7--something that only macros can make happen...

// expands to the assembly instructions that load a string into an address
#define LOAD_STRING_TO_ADDRESS(addr, str) LOAD_STRING_TO_ADDRESS_IMPL1(__COUNTER__, addr, str)
// double expansion needed to stringify the value in `__COUNTER__`
#define LOAD_STRING_TO_ADDRESS_IMPL1(header, addr, str) LOAD_STRING_TO_ADDRESS_IMPL2(header, addr, str)
#define LOAD_STRING_TO_ADDRESS_IMPL2(header, addr, str) \
	".section h"  #header  ";" \
	".set h"  #header  ","  #addr  ";" \
	".string "  #str  ";"

asm(
	// make invalid type errors make sense
	LOAD_STRING_TO_ADDRESS(0xD459B0, "%s expected but got %s\0\0") // from `"attempt to %s a %s value"
	LOAD_STRING_TO_ADDRESS(0xD44F60, "userdata\0\0\0\0\0\0\0")     // from `"use as userdata"`
	LOAD_STRING_TO_ADDRESS(0xE00AD0, "string\0\0\0\0\0\0\0")       // from `"use as string"`
	LOAD_STRING_TO_ADDRESS(0xE00AE0, "boolean\0\0\0\0\0\0\0")      // from `"use as boolean"`
	LOAD_STRING_TO_ADDRESS(0xE01168, "integer\0\0\0\0\0\0\0")      // from `"use as integer"`
	LOAD_STRING_TO_ADDRESS(0xE09310, "thread\0\0\0\0\0\0\0")       // from `"use as thread"`
	LOAD_STRING_TO_ADDRESS(0xE09A50, "number\0\0\0\0\0\0\0")       // from `"use as number"`
	// make logging functions separate arguments with the empty string instead of the literal representation of it
	LOAD_STRING_TO_ADDRESS(0xD47304, "\0\0\0\0")                   // from `R"(\000)"`
);

// wash our hands...
#undef LOAD_STRING_TO_ADDRESS_IMPL2
#undef LOAD_STRING_TO_ADDRESS_IMPL1
#undef LOAD_STRING_TO_ADDRESS
