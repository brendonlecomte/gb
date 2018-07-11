#include "cart.h"
#include <stdio.h>
#include <assert.h>
#include "physical_cart.h"

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
