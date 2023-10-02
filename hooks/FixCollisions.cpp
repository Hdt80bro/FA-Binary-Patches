#include "../define.h"
// This skips the check that makes entries after the first one in the collision
// results list only considered when that entry is the last entry's shield
asm(
  // Moho::Projectile::CheckCollision+0x96E
  ".section h0; .set h0,0x69DB3E;"
  "JMP .+0x6D;"
);