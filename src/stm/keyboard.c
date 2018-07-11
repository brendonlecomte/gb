#include "io.h"

static uint8_t _dir;
static uint8_t _buttons;

void io_init(void){
  _dir = 0xFF;
  _buttons = 0xFF;
}

uint8_t io_get_direction(){
  return _dir;
}

uint8_t io_get_buttons() {
  return _buttons;
}

void io_set_direction(uint8_t dir) {
  _dir = dir;
}

void io_set_buttons(uint8_t buttons) {
  _buttons = buttons;
}
