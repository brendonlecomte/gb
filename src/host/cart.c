#include "cart.h"
#include <stdio.h>
#include <assert.h>

extern uint8_t game_cart[MAX_CART_SIZE];

typedef struct {
  uint8_t ram_write_protect; //reg 0
  uint8_t rom_bank_sel; //reg 1
  uint8_t ram_bank_sel;
  uint8_t latch_clock;
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
  uint8_t day_lower;
  uint8_t day_upper;
} mbc3_t;


uint8_t cart_type = ROM_ONLY;
uint8_t ram_enabled = 0;
uint16_t rom_base;
uint16_t ram_base;

uint8_t rom_read(const uint16_t addr);
uint8_t mbc5_read(const uint16_t addr);

void rom_write(const uint16_t addr, uint8_t val);
void mbc5_write(const uint16_t addr, uint8_t val);


uint8_t (*read_cart)(const uint16_t addr);
void (*write_cart)(const uint16_t addr, uint8_t val);

void cart_load(void) {
  // does nothing handled by script...
  cart_type = game_cart[0x147];
  switch(cart_type) {
    case ROM_ONLY:
      read_cart = rom_read;
      write_cart = rom_write;
      break;
    case MBC5:
      rom_base = 0;
      ram_base = 0;
      read_cart = mbc5_read;
      write_cart = mbc5_write;
      break;
    default:
      break;
  }
}

uint8_t cart_read(const uint16_t addr) {
  read_cart(addr);
}

void cart_write(const uint16_t addr, uint8_t val) {
  write_cart(addr, val);
}

uint8_t* cart_memory(void) {
    return &game_cart[0];
}

cart_t* cart_header(void) {
    return (cart_t *)&game_cart[0x100];
}

uint8_t rom_read(const uint16_t addr){
  return game_cart[addr];
}

uint8_t mbc5_read(const uint16_t addr){
  switch(addr & 0xF000) {
    case 0x0000:
    case 0x1000:
    case 0x2000:
    case 0x3000:
      return game_cart[addr];
      break;
    case 0x2000:
       break;
    case 0x3000:
       break;
    case 0x4000:
    case 0x5000:
       ramPageStart = (data & 0x03) * RAM_PAGESIZE;
       break;
    default:
       super.setAddress(addr, data);
       break;
  }
  return 0;
}

void rom_write(const uint16_t addr, uint8_t val) {

}

void mbc5_write(const uint16_t addr, uint8_t val){
  switch(addr & 0xF000) {
    case 0x0000:
    case 0x1000:
       if (core.cartridge.ramBanks > 0)
           ramEnabled = (data & 0x0F) == 0x0A;
       break;
    case 0xA000:
    case 0xB000:
       if (ramEnabled)
       {
           cartRam[addr - 0xA000 + ramPageStart] = data;
       }
       break;
    case 0x2000:
       break;
    case 0x3000:
       break;
    case 0x4000:
    case 0x5000:
       ramPageStart = (data & 0x03) * RAM_PAGESIZE;
       break;
    default:
       super.setAddress(addr, data);
       break;
  }
}
