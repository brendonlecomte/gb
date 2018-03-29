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
  emu_init();
  for(;;)
  {
    emu_execute();
  }
  emu_end();
  return 0;
}
