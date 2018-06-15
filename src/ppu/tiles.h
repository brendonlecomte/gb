#include <stdint.h>

typedef struct {
    uint8_t map[16]; //16 byte map
} tile_t;

uint8_t tiles_get_palette_index(tile_t* t, uint8_t x, uint8_t y);
