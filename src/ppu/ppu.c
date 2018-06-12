#include "ppu.h"
#include "CPU.h"
#include "memory.h"
#include "memory_locations.h"
#include "debug.h"
#include "lcd.h"
#include <assert.h>

typedef struct {
  uint8_t bg_win_priority:1;
  uint8_t sprite_enable:1;
  uint8_t sprite_size:1;
  uint8_t tile_data:1;
  uint8_t tile_select:1;
  uint8_t window_enable:1;
  uint8_t tile_map_select:1;
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

typedef struct {
    uint8_t map[16]; //16 byte map
} tile_t;

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

uint8_t p[4] = {0,1,2,3};
uint8_t *palette;
tile_t *bg_tiles[2];
uint8_t *background[2];
lcd_control_t *control_reg;
lcd_status_register_t *status_reg;
uint8_t *lcd_y;
uint8_t *lcd_yc;

int_reg_t *interrupts;
uint16_t clocks;

void ppu_init(void) {
    status_reg = (lcd_status_register_t*)&memory->memory[STAT];
    control_reg = (lcd_control_t*)&memory->memory[LCDC];
    lcd_y = &memory->memory[LY];
    lcd_yc = &memory->memory[LYC];
    background[0] = &memory->memory[0x9800];
    background[1] = &memory->memory[0x9C00];

    bg_tiles[0] = (tile_t*)&memory->memory[0x8800];
    bg_tiles[1] = (tile_t*)&memory->memory[0x8000];
    // palette = &memory->memory[BGP];
    palette = &p[0];
    clocks = 0;
    *lcd_y = 0;
    *lcd_yc = 0;
#ifndef UNITTEST
    lcd_init();
#endif
}

void ppu_run(void) {
  clocks += 1;

  switch(status_reg->mode)
  {
    case PPU_OAM:
      if(clocks > OAM_CLOCKS) {
          clocks = 0;
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
        if(control_reg->enable) {
          draw_bg_line(*lcd_y, memory->memory[SCY], memory->memory[SCX]);
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


void draw_screen_line(const uint8_t line, const uint8_t scy, const uint8_t scx) {
  //draw bg

  //draw window

  //draw sprites
}

//BGP is palette
void draw_bg_line(const uint8_t line, const uint8_t scy, const uint8_t scx)
{
    uint8_t y = line + scy;
    uint8_t tile_row = y>>3; //get line of tile map
    uint8_t line_in_tile = (y % 8) << 1;
    for(int i = 0; i < 32; i++) //each tile
    {
        /* Not sure BG tile map display select is used in DMG*/
        uint8_t tile = background[0][tile_row*32 + i]; //get tile index from background map
        /* CGB uses both bg tile chunks bg_tiles[control_reg->tile_data][tile]*/
        tile_t *t = &bg_tiles[1][tile]; //get tile data from tile map
        for(int j = 0; j < 8; j++) //each pixel in tile row
        {
            uint8_t colour=0, a, b, val;
            a = t->map[line_in_tile];
            b = t->map[line_in_tile+1];
            val = (a>>(7-j) &0x01)<<1 | (b>>(7-j) &0x01);
            //TODO: fix this to use memory palette
            colour = palette[val]; //get colour value from the palette

#ifndef UNITTEST
            uint8_t x =(i*8) + j;
            lcd_set_pixel(x+scx, line, colour);
#endif
        }
    }

}

//
// draw background
// draw window
// draw sprites
