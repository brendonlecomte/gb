#include <stdint.h>

#define TILE_WIDTH (8)
#define TILE_ROW_WIDTH (32)

typedef struct {
    uint8_t map[16]; //16 byte map
} tile_t;

void tiles_init(void);
uint8_t tiles_get_palette_index(tile_t* t, uint8_t x, uint8_t y);
tile_t* tiles_get_tile(uint8_t index);
