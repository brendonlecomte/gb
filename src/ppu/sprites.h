#include <stdint.h>
#include <stdbool.h>

#define MAX_SPRITES (40)
#define MAX_SPRITES_PER_LINE (10)


typedef struct {
  uint8_t palette_cgb:3; //cgb only
  bool tile_bank:1; //cgb only
  bool palette:1; //palette select
  bool x_flip:1;
  bool y_flip:1;
  bool bg_priority:1;
} sprite_flags_t;

typedef struct {
  uint8_t pos_y;
  uint8_t pos_x;
  uint8_t tile;
  uint8_t flags;
} sprite_t;

void sprites_search(uint8_t line);
uint8_t* sprites_get_sprite(uint8_t index);
void sprites_draw_line(uint8_t line);
