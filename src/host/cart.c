#include "cart.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define RAM_2K (0x800)
#define RAM_8K (0x2000)

extern uint8_t* game_cart;

typedef struct {
  uint8_t ram_bank_enabled;
  uint8_t ram_write_protect; //reg 0
  uint8_t rom_bank_sel; //reg 1
  uint8_t ram_bank_sel;
  uint8_t rom_ram_mode_sel;
  uint8_t latch_clock;
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
  uint8_t day_lower;
  uint8_t day_upper;
} mbc3_t;

/*private vars*/
static const uint8_t rom_sizes[9] = {0, 4, 8, 16, 32, 64, 128, 256, 512};
static const uint32_t ram_sizes[6] = {0, RAM_2K, RAM_8K, 4*RAM_8K, 16*RAM_8K, 8*RAM_8K};

static mbc3_t mbc;
static uint8_t cart_type = ROM_ONLY;
static uint8_t* ram;
static uint8_t max_rom;

/*private func prototypes*/
uint32_t convert_rom_address(uint16_t addr);
uint8_t rom_read(const uint16_t addr);
uint8_t mbc5_read(const uint16_t addr);

void rom_write(const uint16_t addr, uint8_t val);
void mbc5_write(const uint16_t addr, uint8_t val);

uint8_t (*read_cart)(const uint16_t addr);
void (*write_cart)(const uint16_t addr, uint8_t val);
/*PUBLIC*/
void cart_load(void) {
  // does nothing handled by script...
  cart_t* c = cart_header();
  cart_type = c->cart_type;
  max_rom = rom_sizes[c->rom_size];
  ram = malloc(ram_sizes[c->ram_size]);
  switch(cart_type) {
    case ROM_ONLY:
      read_cart = rom_read;
      write_cart = rom_write;
      break;
    case MBC1:
    case MBC3:
    case MBC3_RAM_BATTERY:
    case MBC5:
      read_cart = mbc5_read;
      write_cart = mbc5_write;
      break;
    default:
      break;
  }
}

uint8_t cart_read(const uint16_t addr) {
  return read_cart(addr);
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

uint8_t* cart_pointer(uint16_t addr) {
  if(mbc.rom_bank_sel != 0 && addr >= 0x4000) {
    printf("rom banked!\n");
    return &game_cart[convert_rom_address(addr)];
  }
  return (uint8_t*)&game_cart[addr];
}

/*PRIVATE*/
uint32_t convert_rom_address(uint16_t addr) {
  return ((addr - 0x4000) + mbc.rom_bank_sel*0x4000);
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
    case 0x4000:
    case 0x5000:
    case 0x6000:
    case 0x7000:
      return game_cart[convert_rom_address(addr)];
      break;
    case 0xA000:
    case 0xB000:
    case 0xC000:
      if(mbc.ram_bank_sel <= 0x03) {
            return ram[(addr - 0xA000) + mbc.ram_bank_sel*RAM_2K];
      }
      else if(0x08 <= mbc.ram_bank_sel && mbc.ram_bank_sel <= 0x0C) {
          return 0;//set the clock
      }
      else {
          assert("Invalid RAM Bank selected");
      }
      break;
    default:
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
      if(val == 0x0A) {
        mbc.ram_bank_enabled = 1;
      }
      else {
        mbc.ram_bank_enabled = 0;
      }
      break;
    case 0x2000:
    case 0x3000:
      if(val == 0){
        val = 1;
      }
      mbc.rom_bank_sel = (mbc.rom_bank_sel & 0b11100000) | (val & 0b00011111);
      break;
    case 0x4000:
    case 0x5000:
      if(mbc.rom_ram_mode_sel){
        mbc.ram_bank_sel = val;
      }
      else {
        mbc.rom_bank_sel = (mbc.rom_bank_sel & 0b00011111) | (val<<5);
      }
      break;
    case 0x6000:
    case 0x7000:
      mbc.rom_ram_mode_sel = val;
      break;
    case 0xA000:
    case 0xB000:
    case 0xC000:
      if(mbc.ram_bank_sel <= 0x03) {
            ram[(addr - 0xA000) + mbc.ram_bank_sel*RAM_2K] = val;
      }
      else if(0x08 <= mbc.ram_bank_sel && mbc.ram_bank_sel <= 0x0C) {
          //set the clock
      }
      else {
          assert("Invalid RAM Bank selected");
      }
      break;
    default:
      break;
  }
}
