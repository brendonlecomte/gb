#include "emulator.h"
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "CPU.h"
#include "memory.h"
#include "memory_locations.h"

int main(int argc, const char * argv[])
{
  uint8_t exit = 1;
  uint8_t old_pc = 0;
  uint16_t step = 0;
  // DEBUG_PRINTF("GB emulator...\n");
  emu_init();
  for(;;)
  {
    emu_execute();
    if(gb_cpu->PC == 0x100 || step == 1)
    {
        printf("Palette: 0x%02X\n", memory->memory[BGP]);
        for(int i = 0x8000; i < 0x8030; i ++){
          printf("0x%02X\n", memory->memory[i]);
        }
        // printf("Palette: 0x%02X\n", memory->memory[BGP]);
        scanf("%d\n", &exit);
        step = 1;
        if(exit == 0) break;
    }
  }
  emu_end();
  return 0;
}
