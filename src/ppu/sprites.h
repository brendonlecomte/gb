#include <stdint.h>
#include <stdbool.h>

#define MAX_SPRITES (40)
#define MAX_SPRITES_PER_LINE (10)

void sprites_search(uint8_t line);
uint8_t* sprites_get_sprite(uint8_t index);
void sprites_draw_line(uint8_t line);
