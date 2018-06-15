#include "tiles.h"


uint8_t tiles_get_palette_index(tile_t* t, uint8_t x, uint8_t y) {
  uint8_t a = t->map[x];
  uint8_t b = t->map[x+1];
  return (a>>(7-y) &0x01)<<1 | (b>>(7-y) &0x01);
}
