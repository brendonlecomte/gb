#include "serial.h"
#include <stdio.h>
#include "debug.h"

void serial_write_byte(uint8_t ch){
  #ifdef SERIAL
  printf("%c", ch);
  #endif
}

uint8_t serial_read_byte(void) {

}
