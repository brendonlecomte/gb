#include "serial.h"
#include "hardware_init.h"
// #include "usbd_cdc_if.h"


static uint8_t _tx_buffer[256];
static uint8_t _buff_index = 0;

void serial_write_byte(uint8_t ch){
  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
  HAL_UART_Transmit(&huart4, &ch, 1, 10);
}

uint8_t serial_read_byte(void) {

}
