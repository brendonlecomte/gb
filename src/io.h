#include <stdint.h>

void io_init(void);
uint8_t io_get_direction(void);
uint8_t io_get_buttons(void);
void io_set_direction(uint8_t dir);
void io_set_buttons(uint8_t buttons);
