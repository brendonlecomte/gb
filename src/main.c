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
  uint16_t i = 100;
  emu_init();
  while(i)
  {
    emu_execute();
    // i--;
  }
  emu_end();
  return 0;
}
