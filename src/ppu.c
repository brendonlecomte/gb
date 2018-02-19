#include "ppu.h"
#include "CPU.h"
#include "memory.h"
#include "memory_locations.h"
#include "debug.h"
#include "lcd.h"
#include <assert.h>

uint8_t p[4] = {0,1,2,3};

uint8_t *palette;
tile_t *tiles;
uint8_t *background;

void draw_line(uint8_t line);

typedef enum {
    PPU_IDLE,
    PPU_OAM,
    PPU_TRANSFER,
    PPU_H_BLANK,
    PPU_V_BLANK
} ppu_mode_t;

lcd_control_t *control_reg;
lcd_status_register_t *status_reg;
uint8_t *lcd_y;
uint8_t *lcd_yc;

int_reg_t *interrupts;
ppu_mode_t mode;
uint16_t clocks;

void ppu_init(void) {
    status_reg = (lcd_status_register_t*)&memory->memory[STAT];
    control_reg = (lcd_control_t*)&memory->memory[LCDC];
    lcd_y = &memory->memory[LY];
    lcd_yc = &memory->memory[LYC];
    background = &memory->memory[0x9800];
    tiles = (tile_t*)&memory->memory[0x8000];
    // palette = &memory->memory[BGP];
    palette = &p[0];
#ifndef UNITTEST
    lcd_init();
#endif
}

void ppu_run(void) {
  clocks += 1;

  switch(mode)
  {
    case PPU_OAM:
      status_reg->mode = 2;
      if(clocks >= 42) {
          mode = PPU_TRANSFER;
      }
      break;

    case PPU_TRANSFER:
      status_reg->mode = 3;

      if(clocks >= 20) {
          mode = PPU_H_BLANK;
          if(status_reg->h_blank_int) status_reg->h_blank_int = 1;
          draw_line(*lcd_y);
      }
      break;

    case PPU_H_BLANK:
      status_reg->mode = 0;
      if(clocks >= 50){
        *lcd_y += 1; //line completed
        clocks = 0; //clear clocks, line complete
        if(*lcd_y == *lcd_yc && status_reg->coincidence_int) status_reg->coincidence_flag = 1;
        if(*lcd_y == 144) {
            if(status_reg->v_blank_int) status_reg->v_blank_int = 1;
            CPU_set_interrupt(gb_cpu, INT_V_BLANK);
            mode = PPU_V_BLANK;
        }
        else {
            mode = PPU_OAM;
        }
      }
      break;

    case PPU_V_BLANK:
      status_reg->mode = 1;
      if(clocks >= 1300){
          if(control_reg->lcd_enable){
#ifndef UNITTEST
          lcd_refresh();
#endif
          }
          clocks =0;
          *lcd_y = 0; //back to top of screen
          mode = PPU_OAM;
          if(status_reg->oam_int) status_reg->oam_int = 1;
      }
      break;

    case PPU_IDLE: //there is no idle
    default:
      mode = PPU_OAM;
      break;
  }
}

void ppu_close(void) {
#ifndef UNITTEST
   lcd_close();
#endif
}


//BGP is palette
void draw_line(uint8_t line)
{
    uint8_t y = line + memory->memory[SCY];
    uint8_t tile_row = y>>3; //get line of tile map
    uint8_t line_in_tile = (y % 8) << 1;
    for(int i = 0; i < 32; i++) //each tile
    {
        uint8_t tile_index = background[tile_row*32 + i]; //get tile index from background map
        tile_t *t = &tiles[tile_index]; //get tile data from tile map
        // if(tile_index != 0) printf("line %d, tile: 0x%02X\n", line, tile_index);
        for(int j = 0; j < 8; j++) //each pixel in tile row
        {
            uint8_t colour=0, a, b, val;
            a = t->map[line_in_tile];
            b = t->map[line_in_tile+1];
            val = (a>>(7-j) &0x01)<<1 | (b>>(7-j) &0x01);
            colour = palette[val]; //get colour value from the palette

            uint8_t x =(i*8) + j;
#ifndef UNITTEST
            lcd_set_pixel(x+memory->memory[SCX], line, colour);
#endif
        }
    }
}
