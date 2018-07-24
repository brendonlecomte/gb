#include "tiles.h"
#include "memory.h"

tile_t *_bg_tiles[2];

void tiles_init(void) {
  _bg_tiles[0] = (tile_t*)&memory->memory[0x8800];
  _bg_tiles[1] = (tile_t*)&memory->memory[0x8000];
}

uint8_t tiles_get_palette_index(tile_t* t, uint8_t x, uint8_t y) {
  uint8_t a = t->map[x];
  uint8_t b = t->map[x+1];
  return (a>>(7-y) &0x01)<<1 | (b>>(7-y) &0x01);
}

tile_t* tiles_get_tile(uint8_t tile_data, uint8_t index) {
  /* CGB uses both bg tile chunks bg_tiles[control_reg->tile_data][tile]*/
  return &_bg_tiles[tile_data][index]; //get tile data from tile map
}
