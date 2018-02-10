#include "cart.h"
#include <stdio.h>
#include <assert.h>

#define CART_PATH ("/Users/brendon/research/gb/roms/cpu_instrs.gb")
#define HOME_CART_PATH ("/Users/brendon/workspace/gb/roms/tetris.gb")

void cart_load(uint8_t *mem, uint16_t size) {
    FILE *f;
    f = fopen(HOME_CART_PATH, "rb");
    if(f){
        fread(mem, 1, size, f);
        fclose(f);
    }
    else{
        printf("Failed to open file\n");
        assert(0);
    }
}
