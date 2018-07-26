#include "tiles.h"
#include "memory.h"

void tiles_init(void) {
  // _bg_tiles[0] = &memory->memory[0x8800];
  // _bg_tiles[1] = &memory->memory[0x8000];
}

uint8_t tiles_get_palette_index(tile_ptr t, uint8_t x, uint8_t y) {
  uint8_t _y = y&0xFE;
  uint8_t a = t[_y];
  uint8_t b = t[_y+1];
  return (a>>(7-x) &0x01)<<1 | (b>>(7-x) &0x01);
}

tile_ptr tiles_get_tile(uint8_t tile_data, uint8_t index) {
  /* CGB uses both bg tile chunks bg_tiles[control_reg->tile_data][tile]*/
  uint16_t addr = tile_data ? 0x8000 : 0x8800;
  uint16_t tile_number;
  // control_reg->bg_win_tile_select if this is 0 then signed tile_number
  if(tile_data == 0) {
    if(index&0x80){
      tile_number = 0x8000 + (((~index))<<4);
    }
    else{
      tile_number = 0x9000 + (index<<4);
    }
    // printf("i:%d t:%d\n",index,tile_number);
    // tile_number = addr + ((index+128)<<4);
  }
  else {
    tile_number = addr + (index<<4);
  }

  return &memory->memory[tile_number]; //get tile data from tile map
}
