#ifndef PPU_H
#define PPU_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
  uint8_t enable:1,
  tile_map_select:1,
  window_enable:1,
  bg_win_tile_select:1,
  bg_tile_select:1,
  sprite_size:1,
  sprite_enable:1,
  bg_win_priority:1;
} lcd_control_t;

typedef struct {
  uint8_t mode:2,
  coincidence_flag:1,
  h_blank_int:1,
  v_blank_int:1,
  oam_int:1, 
  coincidence_int:1,
  unused:1;
} lcd_status_register_t;

typedef struct {
  bool bg_priority:1;
  bool y_flip:1;
  bool x_flip:1;
  bool palette:1;
  bool tile_bank:1; //cgb only
  uint8_t palette_cgb:3; //cgb only
} sprite_flags_t;

typedef struct {
  uint8_t pos_y;
  uint8_t pos_x;
  uint8_t tile;
  sprite_flags_t flags;
} sprite_t;

typedef struct {
    uint8_t map[16]; //16 byte map
} tile_t;

void ppu_init(void);
void ppu_run(void);
void ppu_close(void);

#endif //PPU_H
