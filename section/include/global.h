#pragma once

#include "mscrt.h"
#include "../../workflow.cpp"
#include <type_traits>


#define RECOMPILE 0

#define g_CSimDriver			GPtr(0x10C4F50, CSimDriver*)
#define g_SWldSessionInfo		GPtr(0x10C4F58, SWldSessionInfo*)
#define g_CWldSession			GPtr(0x10A6470, CWldSession*)
#define g_Sim				GPtr(0x10A63F0, Sim*)
#define g_EntityCategoryTypeInfo	GPtr(0x10C6E70, EntityCategoryTypeInfo*)
#define g_CAiBrainTypeInfo		GPtr(0x10C6FA0, CAiBrainTypeInfo*)
#define g_CUIManager			GPtr(0x10A6450, CUIManager*)
#define g_EngineStats			GPtr(0x10A67B8, EngineStats*)
#define g_WRenViewport			GPtr(0x10C7C28, WRenViewport*)
#define g_ConsoleLuaState		GPtr(0x10A6478, LuaState*)
#define g_Device			GPtr(0x0F8E284, Device*)

GDecl(ui_ProgressBarColor,		0x0F57BB8, int)
GDecl(ui_SelectTolerance,		0x0F57A90, float)
GDecl(ui_ExtractSnapTolerance,		0x0F57A94, float)
GDecl(ui_DisableCursorFixing,		0x10A6464, bool)
GDecl(ui_RenderIcons,			0x0F57B27, bool)
GDecl(range_RenderSelected,		0x10A640A, bool)
GDecl(range_RenderHighlighted,		0x10A640B, bool)
GDecl(range_RenderBuild,		0x10A6414, bool)
GDecl(d3d_WindowsCursor,		0x10A636E, bool)
GDecl(debugSelect,			0x10A645E, bool)

GDecl(s_FACTORY,			0xE19824, const char*)
GDecl(s_EXPERIMENTAL,			0xE204B8, const char*)
GDecl(s_ExpectedButGot,			0xE0A220, const char*) // "%s\n  expected %d args, but got %d"
GDecl(s_ExpectedBetweenButGot,		0xE0A270, const char*) // "%s\n  expected between %d and %d args, but got %d"
GDecl(s_Global,				0xE00D90, const char*) // "<global>"
GDecl(s_CMauiBitmap,			0xE37438, const char*) // "CMauiBitmap"
GDecl(s_UserUnit,			0xE4D090, const char*) // "UserUnit"
GDecl(s_ExpectedAGameObject,		0xE09860, const char*) // "Expected a game object. (Did you call with '.' instead of ':'?)"
GDecl(s_GameObjectHasBeenDestroyed,	0xE098A0, const char*) // "Game object has been destroyed"
GDecl(s_IncorrectTypeOfGameObject,	0xE098C0, const char*) // "Incorrect type of game object.  (Did you call with '.' instead of ':'?)"
GDecl(s_UnknownColor,			0x4B2D54, const char*) // "Unknown color: %s"
GDecl(s_c_object,			0xE016DC, const char*) // "_c_object"

GDecl(g_ExeVersion1,			0x876666, const int)
GDecl(g_ExeVersion2,			0x87612d, const int)
GDecl(g_ExeVersion3,			0x4d3d40, const int)

// there's dozens of these around; here's one set
CDecl(NaN,  0x10A7CB0, float);
CDecl(pInf, 0x10B5484, float);
CDecl(nInf, 0x10B5488, float);


void AbortF(wchar_t *fmt, ...) asm("0x9C4940");
int LogF(const char *fmt, ...) asm("0x937CB0");
int WarningF(const char *fmt, ...) asm("0x937D30");
int SpewF(const char *fmt, ...) asm("0x937C30");
int ConsoleLogF(const char *fmt, ...) asm("0x41C990");