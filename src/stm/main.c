#include "main.h"
#include "hardware_init.h"
#include "serial.h"

int main(void)
{
  hardware_init();
  uint8_t buff[12] = "hello world\n";
  while (1)
  {
    for(int i =0; i <12; i++) {
        serial_write_byte(buff[i]);
    }
    HAL_Delay(500);
  }
}
