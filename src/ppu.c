#include "ppu.h"
#include "CPU.h"

typedef enum {
    PPU_IDLE,
    PPU_OAM,
    PPU_TRANSFER,
    PPU_H_BLANK,
    PPU_V_BLANK
} ppu_mode_t;

lcd_status_register_t *status_reg;
uint8_t *lcd_y;
uint16_t *sprites[10]; //max of 10 sprites per line
int_reg_t *interrupts;
ppu_mode_t mode;
uint8_t clocks;

void ppu_init(void) {

}


void ppu_run(void) {
  uint8_t x, y;
  clocks += 1;

  switch(mode)
  {
    case PPU_OAM: //20 clocks
      status_reg->mode = 2;
      if(clocks >= 20) mode = PPU_TRANSFER;
      break;

    case PPU_TRANSFER: //43 clocks
      status_reg->mode = 3;
      if(clocks >= 63) mode = PPU_H_BLANK;
      break;

    case PPU_H_BLANK: //51 clocks
      status_reg->mode = 0;
      if(clocks >= 114){
        clocks = 0; //clear clocks, line complete
        if(*lcd_y == 144) mode = PPU_V_BLANK;
        else mode = PPU_OAM;
      }
      break;

    case PPU_V_BLANK:
      status_reg->mode = 1;
      break;

    case PPU_IDLE: //there is no idle
    default:
      mode = PPU_OAM;
      break;
  }
}

void ppu_close(void) {


}
