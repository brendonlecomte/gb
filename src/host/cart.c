#include "cart.h"
#include <stdio.h>

#define CART_PATH ("/Users/brendon/research/gb/roms/cpu_instrs.gb")

void cart_load(uint8_t *mem, uint16_t size) {
    FILE *f;
    f = fopen(CART_PATH, "rb");
    if(f){
        // fseek(f, 256, SEEK_SET);
        fread(mem, 1, size, f);
        fclose(f);
    }
    else{
        printf("Failed to open file\n");
    }
}