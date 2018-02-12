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

lcd_status_register_t *status_reg;
uint8_t *lcd_y;
// uint16_t *sprites[10]; //max of 10 sprites per line
int_reg_t *interrupts;
ppu_mode_t mode;
uint16_t clocks;

void ppu_init(void) {
    status_reg = (lcd_status_register_t*)&memory->memory[STAT];
    lcd_y = &memory->memory[LY];
    background = &memory->memory[0x9800];
    tiles = (tile_t*)&memory->memory[0x8000];
    // palette = &memory->memory[BGP];
    palette = &p[0];
    lcd_init();
}

uint8_t count =0;
void ppu_run(void) {
  clocks += 1;

  switch(mode)
  {
    case PPU_OAM: //20 clocks
      status_reg->mode = 2;
      if(clocks >= 20) {
          mode = PPU_TRANSFER;
      }
      break;

    case PPU_TRANSFER: //43 clocks
      status_reg->mode = 3;
      if(clocks >= 63) {
          mode = PPU_H_BLANK;
          draw_line(*lcd_y);
      }
      break;

    case PPU_H_BLANK: //51 clocks
      status_reg->mode = 0;
      if(clocks >= 114){
        *lcd_y += 1; //line completed
        clocks = 0; //clear clocks, line complete
        if(*lcd_y == 144){
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
      if(clocks >= 1200){
          lcd_refresh();
          clocks =0;
          *lcd_y = 0; //back to top of screen
          mode = PPU_OAM;
      }
      break;

    case PPU_IDLE: //there is no idle
    default:
      mode = PPU_OAM;
      break;
  }
}

void ppu_close(void) {

    lcd_close();
}


/*
line 0-144
void draw_line(uint8_t lcd_y, uint8_t scx, uint8_t scy){
    uint8_t bg_y = line + SCY;
    uint8_t bg_x = SCX;
    uint8_t tile_row = bg_y / 8; //get row of tile map
    uint8_t tile_col = bg_x / 8; //get col of tile map

    uint8_t line_in_tile = (y % 8) << 1;

    for(uint8_t lcd_x = 0; lcd_x < 144; lcd_x++) //each pixel in the x dimension
    {
        tile_idx = bg[(tile_row*32)+ (x/8)]; //get tile
        tile_t *t = tiles[tile_idx];
        uint8_t pix_off = x % 8;
        a = t->map[line_in_tile];
        b = t->map[line_in_tile+1];
        val = (a>>(7-pix_off) &0x01)<<1 | (b>>(7-pix_off) &0x01);
        col = palette[val];
        led_set_pixel(lcd_x, lcd_y, col); //use absolute line, not y (relative)
    }
}


*/

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
            lcd_set_pixel(x+memory->memory[SCX], line, colour);
        }
    }
}
