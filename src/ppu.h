#ifndef PPU_H
#define PPU_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
  bool lcd_enable:1;
  bool tile_map_select:1;
  bool window_enable:1;
  bool bg_win_tile_select:1;
  bool bg_tile_select:1;
  bool sprite_size:1;
  bool sprite_enable:1;
  bool bg_win_priority:1;
} lcd_control_t;

typedef struct {
  bool unused:1;
  bool coincidence_int:1;
  bool oam_int:1;
  bool v_blank_int:1;
  bool h_blank_int:1;
  bool coincidence_flag:1;
  uint8_t mode:2;
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

void ppu_init(void);
void ppu_run(void);
void ppu_close(void);

#endif //PPU_H
