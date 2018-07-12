#include "serial.h"
#include "usbd_cdc_if.h"

void serial_write_byte(uint8_t ch){
  CDC_Transmit_FS(&ch, 1); //write a single byte to the CDC
}

uint8_t serial_read_byte(void) {

}
