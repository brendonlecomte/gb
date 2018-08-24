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

uint8_t scanline[160];

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
void draw_win_line(const uint8_t line, const uint8_t scy, const uint8_t scx);

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
          draw_bg_line(*lcd_y, memory_read8(memory, SCY), memory_read8(memory, SCX));
          draw_win_line(*lcd_y, memory_read8(memory, WY), memory_read8(memory, WX)-7);
          // sprites_draw_line(*lcd_y);
        }
        //increment line counter, reset clock count
        *lcd_y += 1;
        clocks = 0;
        //LY = LYC, trigger interrupt
        if(*lcd_y == *lcd_yc && status_reg->coincidence_int) CPU_set_interrupt(gb_cpu, INT_LCD_STAT);
        //Reached the end of the visible display. Go to VBLANK
        if(*lcd_y >= SCREEN_LINE_END) {
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
          // draw_bg();
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
    //calc position in bg map
    uint8_t bg_y = ((line + scy) % 256);
    uint8_t bg_x = scx;

    //calc data for the tile row and y
    uint8_t tile_col = bg_x>>3;
    uint8_t tile_row = bg_y>>3; //get line of tile map, turns 256 -> 32.. mapping
    uint8_t tile_y = (bg_y % 8) << 1; // get the y of the tile data

    //store position on display
    uint8_t screen_x = 0, screen_y = line;

    if(line >= 144) return; //stop drawing after 144

    for(int tile_pos = 0; tile_pos < 20; tile_pos++) //20tiles width is 160pixels
    {
        //Calculate where on the BG map the tile is
        uint16_t tile_offset = tile_row*32 + ((tile_col + tile_pos)%32);
        //Get the number from memory
        uint8_t tile_number = map[control_reg->bg_map_select][tile_offset];
        //Use the number to get the tile data
        tile_ptr current_tile = tiles_get_tile(control_reg->bg_win_tile_select, tile_number); //0 means signed , 1 means unsigned
        //Use tile data to draw the tile.
        for(uint8_t tile_x = 0; tile_x < TILE_WIDTH; tile_x++) //each pixel in tile row
        {
            uint8_t colour = 0, pal_index;
            uint8_t _x, _y;
            _x = tile_x; //(*current_tile&0x10) ? (7 - tile_x) : tile_x;
            _y = tile_y; //(*current_tile&0x20) ? (7 - tile_y) : tile_y;
            //get the index for the palette from the tile data
            pal_index = tiles_get_palette_index(current_tile, _x, _y);
            colour = (memory_read8(memory, BGP) >> (pal_index<<1)) & 0x03; //get colour value from the palette
#ifndef UNITTEST
            scanline[screen_x] = colour;
            lcd_set_pixel(screen_x, screen_y, colour);
            screen_x++;
#endif
        }
    }
}

void draw_win_line(const uint8_t line, const uint8_t wy, const uint8_t wx) {
    uint8_t bg_y = line;
    uint8_t bg_x = wx;

    //calc data for the tile row and y
    uint8_t tile_col = bg_x>>3;
    uint8_t tile_row = bg_y>>3; //get line of tile map, turns 256 -> 32.. mapping
    uint8_t tile_y = (bg_y % 8) << 1; // get the y of the tile data

    if(control_reg->window_enable == 0) return;

    if(line < wy) return; //not in the window yet

    //store position on display
    uint8_t screen_x = wx, screen_y = line;

    if(line >= 144) return; //stop drawing after 144

    for(int tile_pos = 0; tile_pos < 20; tile_pos++) //20tiles width is 160pixels
    {
        //Calculate where on the BG map the tile is
        uint16_t tile_offset = tile_row*32 + tile_pos;
        //Get the number from memory
        uint8_t tile_number = map[control_reg->win_map_select][tile_offset];

        //Use the number to get the tile data
        tile_ptr current_tile = tiles_get_tile(control_reg->bg_win_tile_select, tile_number);

        //Use tile data to draw the tile.
        for(uint8_t tile_x = 0; tile_x < TILE_WIDTH; tile_x++) //each pixel in tile row
        {
            uint8_t colour = 0, pal_index;
            uint8_t _x, _y;
            _x = tile_x;
            _y = tile_y;
            //get the index for the palette from the tile data
            pal_index = tiles_get_palette_index(current_tile, _x, _y);
            colour = (memory_read8(memory, BGP) >> (pal_index<<1)) & 0x03; //get colour value from the palette
#ifndef UNITTEST

            lcd_set_pixel(screen_x, screen_y, colour);
            scanline[screen_x] = colour;
            screen_x++;
#endif
        }
    }
}

//
// draw background
// draw window
// draw sprites
