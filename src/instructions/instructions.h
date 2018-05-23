#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "CPU.h"
#include <stdint.h>

void instr_adc(uint8_t* A, uint8_t n);
void instr_add(uint8_t* A, uint8_t n);
void instr_add_HL(uint16_t* hl, uint16_t n);
void instr_add_SP(uint16_t *sp, int8_t n);
void instr_and(uint8_t *A, uint8_t n);
void instr_bit(uint8_t b, uint8_t *r);
void instr_call_n(uint16_t n);
void instr_call_cc(CPU_t *cpu, uint16_t n);
void instr_ccf(void);
void instr_daa(uint8_t *A);
void instr_cp(uint8_t *A, uint8_t n);
void instr_cpl(uint8_t *A);

void instr_inc_n(uint8_t *reg);
void instr_dec_n(uint8_t *reg);
void instr_inc_nn(uint16_t *reg);
void instr_dec_nn(uint16_t *nn);
void instr_di(void);
void instr_ei(void);


void instr_jp( uint16_t addr);
void instr_jp_hl(void);
void instr_jr(uint8_t n);
void instr_halt(void);
void instr_set_b(uint8_t b, uint8_t *r);
void instr_load_ab(uint8_t *A, uint8_t n);
void instr_load_ab16(uint16_t *A, uint16_t B);
void instr_nop(void);
void instr_scf(void);
void instr_sla(uint8_t *n);
void instr_sra(uint8_t *n);
void instr_srl(uint8_t *n);
void instr_rst(uint8_t n);

void instr_or(uint8_t *A, uint8_t n);
void instr_pop(uint16_t *nn);
void instr_push(uint16_t nn);
void instr_res(uint8_t b, uint8_t *r);
void instr_ret(void);

void instr_rl_a(uint8_t *n);
void instr_rrc_a(uint8_t *n);
void instr_rlc_a(uint8_t *n);
void instr_rr_a(uint8_t *n);
void instr_rl(uint8_t *n);
void instr_rlc(uint8_t *n);
void instr_rr(uint8_t *n);
void instr_rrc(uint8_t *n);
void instr_sbc(uint8_t *A, uint8_t n);
void instr_sub_n(uint8_t *A, uint8_t n);
void instr_stop(void);
void instr_swap(uint8_t *n);
void instr_xor(uint8_t *A, uint8_t n);
#endif // INSTRUCTIONS_H
