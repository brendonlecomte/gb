#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>
#include "CPU.h"

void instr_adc(CPU_t *cpu, uint8_t n);
void instr_add_A(CPU_t *cpu, uint8_t n);
void instr_add_HL(CPU_t *cpu, uint16_t n);
void instr_add_SP(CPU_t *cpu, uint8_t n);
void instr_and(CPU_t *cpu, uint8_t n);
void instr_bit(CPU_t *cpu, uint8_t b, uint8_t r);

void instr_ccf(CPU_t *cpu);

void instr_cpl(CPU_t *cpu);

#endif // INSTRUCTIONS_H
