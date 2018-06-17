#include "sprites.h"
#include "tiles.h"
#include "memory.h"
#include "memory_locations.h"
#include "lcd.h"
#include <assert.h>

static sprite_t* _sprites[10];
static uint8_t _index = 0;

#define POS_Y (0)
#define POS_X (1)
#define TILE  (2)
#define FLAGS (3)
#define SPRITE_LENGTH (4)

static uint8_t p[4] = {0,1,2,3};

void sprites_search(uint8_t line) {
  _index = 0; //reset count
  for(uint8_t i = 0; i < MAX_SPRITES; i++) {
    uint8_t* s = sprites_get_sprite(i);
    if(s[POS_Y] != 0 && line >= s[POS_Y]-16 && line <= s[POS_Y]-8) {
      _sprites[_index] = s;
      _index++;
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

void sprites_draw_line(uint8_t line) {
  // for(int8_t i = _index; i > 0; i--) {
  //   uint8_t* s = _sprites[i];
  //   for(uint8_t x = s[POS_X]; x < s[POS_X]+8; x++) {
  //     uint8_t colour = 0, pal_index;
  //     tile_t* t;
  //     pal_index = tiles_get_palette_index(t, x, line);
  //     #ifndef UNITTEST
  //       colour = p[pal_index];
  //       lcd_set_pixel(x, line, colour);
  //     #endif
  //   }
  // }
}
