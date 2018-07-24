#include "ppu.h"
#include "CPU.h"
#include "memory.h"
#include "memory_locations.h"
#include "debug.h"
#include "lcd.h"
#include "tiles.h"
#include "sprites.h"
#include <assert.h>



typedef struct {
  uint8_t bg_win_priority:1;
  uint8_t sprite_enable:1;
  uint8_t sprite_size:1;
  uint8_t bg_map_select:1;
  uint8_t bg_win_tile_select:1;
  uint8_t window_enable:1;
  uint8_t win_map_select:1;
  uint8_t enable:1;
} lcd_control_t;

typedef struct {
  uint8_t mode:2;
  uint8_t coincidence_flag:1;
  uint8_t h_blank_int:1;
  uint8_t v_blank_int:1;
  uint8_t oam_int:1;
  uint8_t coincidence_int:1;
  uint8_t unused:1;
} lcd_status_register_t;

/* CGB MODE ONLY */
typedef struct {
  uint8_t palette:3;
  uint8_t tile_bank:1;
  uint8_t unused:1;
  uint8_t h_flip:1;
  uint8_t v_flip:1;
  uint8_t bg_oam_priority:1;
} bg_map_t;



#define OAM_CLOCKS          (80)
#define TRANSFER_CLOCKS     (172)
#define HBLANK_CLOCKS       (204)
#define LINE_CLOCKS         (OAM_CLOCKS + TRANSFER_CLOCKS + HBLANK_CLOCKS)

#define SCREEN_LINE_END (144)
#define VBLANK_LINE_END (250)

#define PPU_OAM         (2)
#define PPU_TRANSFER    (3)
#define PPU_H_BLANK     (0)
#define PPU_V_BLANK     (1)

void draw_bg_line(const uint8_t line, const uint8_t scy, const uint8_t scx);
void draw_window_line(const uint8_t line);

static uint8_t *map[2]; //bg tile map
static lcd_control_t *control_reg;
static lcd_status_register_t *status_reg;
static uint8_t *lcd_y;
static uint8_t *lcd_yc;
static uint16_t clocks;

void ppu_init(void) {
    status_reg = (lcd_status_register_t*)&memory->memory[STAT];
    control_reg = (lcd_control_t*)&memory->memory[LCDC];
    lcd_y = &memory->memory[LY];
    lcd_yc = &memory->memory[LYC];
    map[0] = &memory->memory[0x9800];
    map[1] = &memory->memory[0x9C00];

    tiles_init();

    clocks = 0;
    *lcd_y = 0;
    *lcd_yc = 0;
#ifndef UNITTEST
    lcd_init();
#endif
}

void ppu_run(void) {
  static uint8_t line_to_draw = 1;
  clocks += 1;

  switch(status_reg->mode)
  {
    case PPU_OAM:
      if(clocks > OAM_CLOCKS) {
          line_to_draw = 1;
          clocks = 0;
          sprites_search(*lcd_y); //do the OAM search for sprites
          status_reg->mode = PPU_TRANSFER;
      }
      break;

    case PPU_TRANSFER:
      if(clocks > TRANSFER_CLOCKS) {
          status_reg->mode = PPU_H_BLANK;
          clocks = 0;
          if(status_reg->h_blank_int) CPU_set_interrupt(gb_cpu, INT_LCD_STAT);
      }
      break;

    case PPU_H_BLANK:
      if(clocks > HBLANK_CLOCKS){
        //if the screen is enabled, draw a line to the display
        if(control_reg->enable && line_to_draw) {
          line_to_draw = 0;
          draw_bg_line(*lcd_y, memory->memory[SCY], memory->memory[SCX]);
          draw_window_line(*lcd_y);
          sprites_draw_line(*lcd_y);

        }
        //increment line counter, reset clock count
        *lcd_y += 1;
        clocks = 0;
        //LY = LYC, trigger interrupt
        if(*lcd_y == *lcd_yc && status_reg->coincidence_int) CPU_set_interrupt(gb_cpu, INT_LCD_STAT);
        //Reached the end of the visible display. Go to VBLANK
        if(*lcd_y > SCREEN_LINE_END) {
            CPU_set_interrupt(gb_cpu, INT_V_BLANK); //Trigger VBLANK int
            status_reg->mode = PPU_V_BLANK;
            if(status_reg->v_blank_int) CPU_set_interrupt(gb_cpu, INT_LCD_STAT);
        }
        else {
            if(status_reg->oam_int) CPU_set_interrupt(gb_cpu, INT_LCD_STAT);
            status_reg->mode = PPU_OAM;
        }
      }
      break;

    case PPU_V_BLANK:
      if(clocks > LINE_CLOCKS){
        *lcd_y += 1; //line completed
        clocks = 0;
      }
      if(*lcd_y > VBLANK_LINE_END){
#ifndef UNITTEST
          lcd_refresh();
#endif
          clocks = 0;
          *lcd_y = 0; //back to top of screen
          status_reg->mode = PPU_OAM;
          if(status_reg->oam_int) CPU_set_interrupt(gb_cpu, INT_LCD_STAT);
      }
      break;

    default:
      status_reg->mode = PPU_OAM;
      break;
  }
}

void ppu_close(void) {
#ifndef UNITTEST
   lcd_close();
#endif
}


//BGP is palette
void draw_bg_line(const uint8_t line, const uint8_t scy, const uint8_t scx) {
    uint8_t y = line + scy;
    uint8_t tile_row = y>>3; //get line of tile map, turns 256 -> 32.. mapping
    uint8_t tile_x = (y % 8) << 1;
    for(int tile_index = 0; tile_index < TILE_ROW_WIDTH; tile_index++) //each tile in the bg map
    {
        uint8_t index = map[control_reg->bg_map_select][(tile_row*TILE_ROW_WIDTH) + tile_index];
        tile_t* current_tile = tiles_get_tile(control_reg->bg_win_tile_select, index);
        for(uint8_t tile_y = 0; tile_y < TILE_WIDTH; tile_y++) //each pixel in tile row
        {
            uint8_t colour = 0, pal_index;
            pal_index = tiles_get_palette_index(current_tile, tile_x, tile_y);
            //TODO: fix this to use memory palette
            colour = (memory->memory[BGP] >> (pal_index<<1)) & 0x03; //get colour value from the palette
#ifndef UNITTEST
            uint8_t x = (tile_index*8) + tile_y;
            lcd_set_pixel(x+scx, line, colour);
#endif
        }
    }
}

void draw_window_line(const uint8_t line) {
    uint8_t y = line;
    uint8_t tile_row = y>>3; //get line of tile map, turns 256 -> 32.. mapping
    uint8_t tile_y = (y % 8) << 1;

    //window enabled? -> return
    if(control_reg->window_enable == 0) {
      return;
    }

    //x > 159 -> return

    //y > 143 -> return
    if(line > 143) {
      return;
    }

    for(int tile_index = 0; tile_index < 20; tile_index++) //each tile in the bg map
    {
        uint8_t index = map[control_reg->win_map_select][(tile_row*TILE_ROW_WIDTH) + tile_index];
        tile_t* current_tile = tiles_get_tile(control_reg->bg_win_tile_select, index);
        for(uint8_t tile_x = 0; tile_x < TILE_WIDTH; tile_x++) //each pixel in tile row
        {
            uint8_t colour = 0, pal_index;
            pal_index = tiles_get_palette_index(current_tile, tile_x, tile_y);
            //TODO: fix this to use memory palette
            colour = (memory->memory[BGP] >> (pal_index<<1)) & 0x03; //get colour value from the palette
#ifndef UNITTEST
            uint8_t x = (tile_index*8) + tile_x;
            lcd_set_pixel(x, line, colour);
#endif
        }
    }
}
//
// draw background
// draw window
// draw sprites
