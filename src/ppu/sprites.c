#include "sprites.h"
#include "tiles.h"
#include "memory.h"
#include "memory_locations.h"
#include "lcd.h"
#include <assert.h>

#define PALETTE_CGB(x) (0x07 & x) //cgb only
#define TILE_BANK(x) ((0x08 & x) == 0x08) //cgb only
#define PALETTE_DMG(x) ((0x10 & x) == 0x04) //palette select
#define X_FLIP(x) ((0x20 & x) == 0x20)
#define Y_FLIP(x) ((0x40 & x) == 0x40)
#define BG_PRIORITY(x) ((0x80 & x) == 0x80)

static uint8_t* _sprites[10];
static uint8_t _index = 0;

#define POS_Y (0)
#define POS_X (1)
#define TILE  (2)
#define FLAGS (3)
#define SPRITE_LENGTH (4)

void sprites_search(uint8_t line) {
  _index = 0; //reset count
  for(uint8_t i = 0; i < MAX_SPRITES; i++) {
    uint8_t* s = sprites_get_sprite(i);
    if(s[POS_X] != 0 || s[POS_X] != 168 || s[POS_Y] != 0 || s[POS_Y] != 160){
      if(s[POS_Y] != 0 && line >= s[POS_Y]-16 && line < s[POS_Y]-8) {
        _sprites[_index] = s;
        _index++;
      }
    }
    if(_index >= MAX_SPRITES_PER_LINE) break; //cannot have more than 10
  }
}

uint8_t* sprites_get_sprite(uint8_t index) {
  uint8_t* sprite;
  uint16_t sprite_addr = SPRITES + (index * SPRITE_LENGTH); //4bytes of memory per sprite
  //development assert, protect against out of OAM Sprite memory access
  assert(index < MAX_SPRITES);
  sprite = &memory->memory[sprite_addr];
  return sprite;
}


uint8_t sprites_draw_pixel(uint8_t x, uint8_t y) {

}


void sprites_draw_line(uint8_t line) {
  for(int8_t i = _index; i > 0; i--) {
    uint8_t* s = _sprites[i-1];
    tile_t* t = tiles_get_tile(1, s[TILE]);
    uint8_t y = (line % 8) << 1;
    for(uint8_t x = 0; x < 8; x++) {
      uint8_t colour = 0, pal_index;
      pal_index = tiles_get_palette_index(t, y, x);
    #ifndef UNITTEST
      if(pal_index == 0) {// && !BG_PRIORITY(s[FLAGS])){
        continue;
      }
      if(PALETTE_DMG(*s)){
        colour = (memory->memory[OBP1] >> (pal_index<<1)) & 0x03;
      }
      else {
        colour = (memory->memory[OBP0] >> (pal_index<<1)) & 0x03;
      }

      uint8_t x_draw = x+(s[POS_X]-8);
      lcd_set_pixel(x_draw, line, colour);
    #endif
    }
  }
}
