#include "emulator.h"
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "CPU.h"
#include "memory.h"
#include "memory_locations.h"

int main(void)
{
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
