#include "cart.h"
#include <stdio.h>
#include <assert.h>


#define TEST_ALL_PATH ("/Users/brendon/research/gb/roms/cpu_instrs.gb")
#define TEST_OPUS_PATH ("/Users/brendon/research/gb/roms/opus5.gb")
#define TEST_01_PATH ("/Users/brendon/research/gb/roms/individual/01-special.gb")
#define TEST_02_PATH ("/Users/brendon/research/gb/roms/individual/02-interrupts.gb")
#define TEST_03_PATH ("/Users/brendon/research/gb/roms/individual/03-op sp,hl.gb")
#define TEST_04_PATH ("/Users/brendon/research/gb/roms/individual/04-op r,imm.gb")
#define TEST_05_PATH ("/Users/brendon/research/gb/roms/individual/05-op rp.gb")
#define TEST_06_PATH ("/Users/brendon/research/gb/roms/individual/06-ld r,r.gb")
#define TEST_07_PATH ("/Users/brendon/research/gb/roms/individual/07-jr,jp,call,ret,rst.gb")
#define TEST_08_PATH ("/Users/brendon/research/gb/roms/individual/08-misc instrs.gb")
#define TEST_09_PATH ("/Users/brendon/research/gb/roms/individual/09-op r,r.gb")
#define TEST_10_PATH ("/Users/brendon/research/gb/roms/individual/10-bit ops.gb")
#define TEST_11_PATH ("/Users/brendon/research/gb/roms/individual/11-op a,(hl).gb")
#define HOME_CART_PATH ("/Users/brendon/research/gb/roms/tetris.gb")


extern uint8_t* game_cart;


void cart_load(void) {
  // does nothing handled by script...
}

uint8_t cart_read(const uint16_t addr) {
    return game_cart[addr];
}

void cart_write(const uint16_t addr, uint8_t val)
{

}

uint8_t* cart_memory(void) {
    return &game_cart[0];
}

cart_t* cart_header(void) {
    return (cart_t *)&game_cart[0x100];
}
