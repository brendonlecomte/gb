#include "ppu.h"
#include "CPU.h"
#include "memory.h"
#include "memory_locations.h"
#include "debug.h"
#include "lcd.h"
#include <assert.h>

uint8_t p[4] = {0,1,2,3};

uint8_t *palette;
tile_t *bg_tiles[2];
uint8_t *background;

#define OAM_CLOCKS          (80) //(20)
#define TRANSFER_CLOCKS     (172) //(42)
#define HBLANK_CLOCKS       (204) //(51)
#define LINE_CLOCKS         (OAM_CLOCKS + TRANSFER_CLOCKS + HBLANK_CLOCKS) //(114)

#define SCREEN_LINE_END (144)
#define VBLANK_LINE_END (154)

void draw_bg_line(const uint8_t line, const uint8_t scy, const uint8_t scx);


#define PPU_OAM         (2)
#define PPU_TRANSFER    (3)
#define PPU_H_BLANK     (0)
#define PPU_V_BLANK     (1)

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
    background = &memory->memory[0x9800];

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
      if(clocks >= OAM_CLOCKS) {
          status_reg->mode = PPU_TRANSFER;
      }
      break;

    case PPU_TRANSFER:
      if(clocks >= TRANSFER_CLOCKS) {
          status_reg->mode = PPU_H_BLANK;
          if(status_reg->h_blank_int) status_reg->h_blank_int = 1;
          draw_bg_line(*lcd_y, memory->memory[SCY], memory->memory[SCX]);
      }
      break;

    case PPU_H_BLANK:
      if(clocks >= HBLANK_CLOCKS){
        *lcd_y += 1; //line completed
        clocks = 0; //clear clocks, line complete
        if(*lcd_y == *lcd_yc && status_reg->coincidence_int) status_reg->coincidence_flag = 1;
        if(*lcd_y == SCREEN_LINE_END) {
            if(status_reg->v_blank_int) status_reg->v_blank_int = 1;
            CPU_set_interrupt(gb_cpu, INT_V_BLANK);
            status_reg->mode = PPU_V_BLANK;
        }
        else {
            status_reg->mode = PPU_OAM;
        }
      }
      break;

    case PPU_V_BLANK:
      if(clocks >= LINE_CLOCKS){
        *lcd_y += 1; //line completed
        clocks = 0;
      }
      if(*lcd_y > VBLANK_LINE_END){
          if(control_reg->enable){
#ifndef UNITTEST
          lcd_refresh();
#endif
          }
          clocks = 0;
          *lcd_y = 0; //back to top of screen
          status_reg->mode = PPU_OAM;
          if(status_reg->oam_int) status_reg->oam_int = 1;
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
void draw_bg_line(const uint8_t line, const uint8_t scy, const uint8_t scx)
{
    uint8_t y = line + scy;
    uint8_t tile_row = y>>3; //get line of tile map
    uint8_t line_in_tile = (y % 8) << 1;
    for(int i = 0; i < 32; i++) //each tile
    {
        uint8_t tile_index = background[tile_row*32 + i]; //get tile index from background map
        tile_t *t = &bg_tiles[control_reg->bg_tile_select][tile_index]; //get tile data from tile map
        // if(tile_index != 0) printf("line %d, tile: 0x%02X\n", line, tile_index);
        for(int j = 0; j < 8; j++) //each pixel in tile row
        {
            uint8_t colour=0, a, b, val;
            a = t->map[line_in_tile];
            b = t->map[line_in_tile+1];
            val = (a>>(7-j) &0x01)<<1 | (b>>(7-j) &0x01);
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
