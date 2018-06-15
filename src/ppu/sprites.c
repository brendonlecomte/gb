#include "sprite.h"
#include "memory.h"
#include "memory_locations.h"
#include <assert.h>

sprite_t* sprite_get(uint8_t index) {
  sprite_t* sprite;

  //development assert, protect against out of OAM Sprite memory access
  assert(index < 40);

  sprite = &memory->memory[SPRITES+index];
  return sprite
}
