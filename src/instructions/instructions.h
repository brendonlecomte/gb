#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "CPU.h"
#include <stdint.h>

void instr_adc(uint8_t* A, uint8_t n);
void instr_add(uint8_t* A, uint8_t n);
void instr_add_HL(uint16_t* hl, uint16_t n);
void instr_add_SP(uint16_t *sp, uint8_t n);
void instr_and(uint8_t *A, uint8_t n);
void instr_bit(uint8_t *b, uint8_t *r);
void instr_call_n(uint16_t n);
void instr_call_cc(CPU_t *cpu, uint16_t n);
void instr_ccf(void);

void instr_cpl(uint8_t *A);

void instr_inc_n(uint8_t *reg);
void instr_inc_nn(uint16_t *reg);


void instr_jp(CPU_t *cpu, uint16_t addr);
void instr_jp_hl(CPU_t *cpu);
void instr_jr(CPU_t *cpu, uint8_t n);
void instr_load_an(CPU_t *cpu, uint8_t n);
void instr_load_na(CPU_t *cpu, uint8_t *n);
void instr_nop(CPU_t *cpu);
void instr_sla(CPU_t *cpu, uint8_t n);
void instr_sra(CPU_t *cpu, uint8_t n);
void instr_srl(CPU_t *cpu, uint8_t n);
void instr_xor(CPU_t *cpu, uint8_t n);
#endif // INSTRUCTIONS_H
