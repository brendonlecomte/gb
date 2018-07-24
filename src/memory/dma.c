#include "dma.h"
#include "memory.h"
#include <string.h>

void dma_transfer(uint8_t* start) {
  //cpy mem from start -> DMA_TARGET
  memcpy(&memory->memory[DMA_TARGET], start, 160);
}
