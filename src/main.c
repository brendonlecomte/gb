#include "emulator.h"
#include <stdio.h>
#include <stdint.h>
#include "CPU.h"

int main(int argc, const char * argv[])
{
  uint8_t exit = 1;
  uint8_t old_pc = 0;
  // DEBUG_PRINTF("GB emulator...\n");
  emu_init();
  for(;;)
  {
    emu_execute();
    if(gb_cpu->PC == 0x100) scanf("%d\n", &exit);
  }
  emu_end();
  return 0;
}
