#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>
#include "CPU.h"

void instr_adc(CPU_t* reg, uint8_t n);
void instr_add(CPU_t* reg, uint8_t n);

#endif // INSTRUCTIONS_H
