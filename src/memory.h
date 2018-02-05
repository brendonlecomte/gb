#ifndef MEMORY_H
#define MEMORY_H

#include <stdbool.h>
#include <stdint.h>
#include "memory_locations.h"


typedef struct {
  uint8_t *cart;
  uint8_t *cart_header;
  uint8_t *vram;
  uint8_t *eram;
  uint8_t *ram;
  uint8_t *oam;
  uint8_t *io;
  uint8_t *hram;

  uint8_t memory[FULL_MEMORY];
} memory_t;

extern memory_t *memory;

void memory_init(memory_t *mem);
void memory_load_cart(memory_t *mem);
uint8_t memory_read8(memory_t *mem, uint16_t addr);
uint16_t memory_read16(memory_t *mem, uint16_t addr);

void memory_write8(memory_t *mem, uint16_t addr, uint8_t val);
void memory_write16(memory_t *mem, uint16_t addr, uint16_t val);

#endif // MEMORY_H
