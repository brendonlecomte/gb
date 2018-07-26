#include <stdint.h>

#define TILE_WIDTH (8)
#define TILE_ROW_WIDTH (20) //todo changing this to 20 screws things up

typedef uint8_t* tile_ptr;

void tiles_init(void);
uint8_t tiles_get_palette_index(tile_ptr t, uint8_t x, uint8_t y);
tile_ptr tiles_get_tile(uint8_t tile_data, uint8_t index);
