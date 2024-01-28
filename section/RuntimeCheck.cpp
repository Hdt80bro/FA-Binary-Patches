#include "include/moho.h"

#define _STRINGIFY(X) #X
#define STRINGIFY(X) _STRINGIFY(X)

#define FIELD_AT_POSITION(T, field, offset) do {\
  T obj;\
  int expected = offset;\
  int actual = (int)&obj.field - (int)&obj;\
  if (actual != expected) {\
    LogF(STRINGIFY(T) "::" STRINGIFY(field) " is at %d (%d expected)", actual, expected);\
  }\
} while (false)



void RuntimeCheck() {
    FIELD_AT_POSITION(CScriptObject,cobj, 0xC);
    FIELD_AT_POSITION(CScriptObject,luaobj, 0x20);
    FIELD_AT_POSITION(Projectile,collideSurface, 0x2a8);
}