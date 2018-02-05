#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "CPU.h"
#include "memory.h"
#include "ppu.h"


typedef struct {
  ppu_t *ppu;
  CPU_t *cpu;
  memory_t *mem;
}


#endif //GAMEBOY_H
