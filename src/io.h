#include <stdint.h>

#define DPAD_UP    (0x08)
#define DPAD_DOWN  (0x07)
#define DPAD_LEFT  (0x0D)
#define DPAD_RIGHT (0x0E)

#define BUTTON_A       (0x0E)
#define BUTTON_B       (0x0D)
#define BUTTON_START   (0x07)
#define BUTTON_SELECT  (0x0B)

void io_init(void);
uint8_t io_get_direction(void);
uint8_t io_get_buttons(void);
void io_set_direction(uint8_t dir);
void io_set_buttons(uint8_t buttons);
