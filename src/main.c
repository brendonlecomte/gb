#include "emulator.h"
#include <stdio.h>
#include <stdint.h>

int main(int argc, const char * argv[])
{
  uint8_t exit = 1;
  uint8_t old_pc = 0;
  // DEBUG_PRINTF("GB emulator...\n");
  emu_init();
  for(;;)
  {
    emu_execute();
    scanf("%d\n", &exit);
  }
  return 0;
}
