#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdint.h>


void serial_write_byte(uint8_t ch);
uint8_t serial_read_byte(void);

#endif
