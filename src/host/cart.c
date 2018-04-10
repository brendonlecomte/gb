#include "cart.h"
#include <stdio.h>
#include <assert.h>

#define CART_PATH ("/Users/brendon/research/gb/roms/cpu_instrs.gb")
#define HOME_CART_PATH ("/Users/brendon/research/gb/roms/tetris.gb")

#define MAX_CART_SIZE (0x8000)

static uint8_t cart[MAX_CART_SIZE];

void cart_load(void) {
    FILE *f;
    f = fopen(CART_PATH, "rb");
    if(f){
        fread(cart, 1, MAX_CART_SIZE, f);
        fclose(f);
    }
    else{
        printf("Failed to open file\n");
        assert(0);
    }
}

uint8_t cart_read(const uint16_t addr) {
    return cart[addr];
}

uint8_t* cart_memory(void) {
    return &cart[0];
}
