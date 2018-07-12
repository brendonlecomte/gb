#include "main.h"
#include "hardware_init.h"
#include "serial.h"
#include "emulator.h"


int main(void)
{
  hardware_init();
  emu_init();
  // uint8_t buff[12] = "hello world\n";
  while (1)
  {
    // HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
    // HAL_Delay(50);
    emu_execute();
  }
  emu_end();
  return 0;
}
