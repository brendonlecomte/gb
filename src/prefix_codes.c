#include "CPU.h"
#include "instructions.h"
#include "memory.h"
#include "op_codes.h"
#include <stdio.h>

void RLC_B(void) { printf("Called %s\n", __func__); instr_rlc(gb_cpu->B); gb_cpu->cycles += 4;}
void RLC_C(void) { printf("Called %s\n", __func__); instr_rlc(gb_cpu->C); gb_cpu->cycles += 4;}
void RLC_D(void) { printf("Called %s\n", __func__); instr_rlc(gb_cpu->D); gb_cpu->cycles += 4;}
void RLC_E(void) { printf("Called %s\n", __func__); instr_rlc(gb_cpu->E); gb_cpu->cycles += 4;}
void RLC_H(void) { printf("Called %s\n", __func__); instr_rlc(gb_cpu->H); gb_cpu->cycles += 4;}
void RLC_L(void) { printf("Called %s\n", __func__); instr_rlc(gb_cpu->L); gb_cpu->cycles += 4;}
void RLC_HLm(void) {
    printf("Called %s\n", __func__);
    uint8_t val = memory_read8(memory, *gb_cpu->HL);
    instr_rlc(&val);
    memory_write8(memory, *gb_cpu->HL, val);
    gb_cpu->cycles += 12;
}
void RLC_A(void) { printf("Called %s\n", __func__); instr_rlc(gb_cpu->A); gb_cpu->cycles += 4;}

void RRC_B(void) { printf("Called %s\n", __func__); instr_rrc(gb_cpu->B); gb_cpu->cycles += 4;}
void RRC_C(void) { printf("Called %s\n", __func__); instr_rrc(gb_cpu->C); gb_cpu->cycles += 4;}
void RRC_D(void) { printf("Called %s\n", __func__); instr_rrc(gb_cpu->D); gb_cpu->cycles += 4;}
void RRC_E(void) { printf("Called %s\n", __func__); instr_rrc(gb_cpu->E); gb_cpu->cycles += 4;}
void RRC_H(void) { printf("Called %s\n", __func__); instr_rrc(gb_cpu->H); gb_cpu->cycles += 4;}
void RRC_L(void) { printf("Called %s\n", __func__); instr_rrc(gb_cpu->L); gb_cpu->cycles += 4;}
void RRC_HLm(void) { printf("Called %s\n", __func__); }
void RRC_A(void) { printf("Called %s\n", __func__); instr_rrc(gb_cpu->A); gb_cpu->cycles += 4;}

void RL_B(void) { printf("Called %s\n", __func__); instr_rl(gb_cpu->B); gb_cpu->cycles += 4;}
void RL_C(void) { printf("Called %s\n", __func__); instr_rl(gb_cpu->C); gb_cpu->cycles += 4;}
void RL_D(void) { printf("Called %s\n", __func__); instr_rl(gb_cpu->D); gb_cpu->cycles += 4;}
void RL_E(void) { printf("Called %s\n", __func__); instr_rl(gb_cpu->E); gb_cpu->cycles += 4;}
void RL_H(void) { printf("Called %s\n", __func__); instr_rl(gb_cpu->H); gb_cpu->cycles += 4;}
void RL_L(void) { printf("Called %s\n", __func__); instr_rl(gb_cpu->L); gb_cpu->cycles += 4;}
void RL_HLm(void) { printf("Called %s\n", __func__); }
void RL_A(void) { printf("Called %s\n", __func__); instr_rl(gb_cpu->A); gb_cpu->cycles += 4;}

void RR_B(void) { printf("Called %s\n", __func__); instr_rr(gb_cpu->B); gb_cpu->cycles += 4;}
void RR_C(void) { printf("Called %s\n", __func__); instr_rr(gb_cpu->C); gb_cpu->cycles += 4;}
void RR_D(void) { printf("Called %s\n", __func__); instr_rr(gb_cpu->D); gb_cpu->cycles += 4;}
void RR_E(void) { printf("Called %s\n", __func__); instr_rr(gb_cpu->E); gb_cpu->cycles += 4;}
void RR_H(void) { printf("Called %s\n", __func__); instr_rr(gb_cpu->H); gb_cpu->cycles += 4;}
void RR_L(void) { printf("Called %s\n", __func__); instr_rr(gb_cpu->L); gb_cpu->cycles += 4;}
void RR_HLm(void) { printf("Called %s\n", __func__); }
void RR_A(void) { printf("Called %s\n", __func__); instr_rr(gb_cpu->A); gb_cpu->cycles += 4;}

void SLA_B(void) { printf("Called %s\n", __func__); instr_sla(*gb_cpu->B); gb_cpu->cycles += 4;}
void SLA_C(void) { printf("Called %s\n", __func__); instr_sla(*gb_cpu->C); gb_cpu->cycles += 4;}
void SLA_D(void) { printf("Called %s\n", __func__); instr_sla(*gb_cpu->D); gb_cpu->cycles += 4;}
void SLA_E(void) { printf("Called %s\n", __func__); instr_sla(*gb_cpu->E); gb_cpu->cycles += 4;}
void SLA_H(void) { printf("Called %s\n", __func__); instr_sla(*gb_cpu->H); gb_cpu->cycles += 4;}
void SLA_L(void) { printf("Called %s\n", __func__); instr_sla(*gb_cpu->L); gb_cpu->cycles += 4;}
void SLA_HLm(void) { printf("Called %s\n", __func__); }
void SLA_A(void) { printf("Called %s\n", __func__); instr_sla(*gb_cpu->A); gb_cpu->cycles += 4;}

void SRA_B(void) { printf("Called %s\n", __func__); instr_sra(*gb_cpu->B); gb_cpu->cycles += 4;}
void SRA_C(void) { printf("Called %s\n", __func__); instr_sra(*gb_cpu->C); gb_cpu->cycles += 4;}
void SRA_D(void) { printf("Called %s\n", __func__); instr_sra(*gb_cpu->D); gb_cpu->cycles += 4;}
void SRA_E(void) { printf("Called %s\n", __func__); instr_sra(*gb_cpu->E); gb_cpu->cycles += 4;}
void SRA_H(void) { printf("Called %s\n", __func__); instr_sra(*gb_cpu->H); gb_cpu->cycles += 4;}
void SRA_L(void) { printf("Called %s\n", __func__); instr_sra(*gb_cpu->L); gb_cpu->cycles += 4;}
void SRA_HLm(void) { printf("Called %s\n", __func__); }
void SRA_A(void) { printf("Called %s\n", __func__); instr_sra(*gb_cpu->A); gb_cpu->cycles += 4;}

void SWAP_B(void) { printf("Called %s\n", __func__); instr_swap(gb_cpu->B); gb_cpu->cycles += 4;}
void SWAP_C(void) { printf("Called %s\n", __func__); instr_swap(gb_cpu->C); gb_cpu->cycles += 4;}
void SWAP_D(void) { printf("Called %s\n", __func__); instr_swap(gb_cpu->D); gb_cpu->cycles += 4;}
void SWAP_E(void) { printf("Called %s\n", __func__); instr_swap(gb_cpu->E); gb_cpu->cycles += 4;}
void SWAP_H(void) { printf("Called %s\n", __func__); instr_swap(gb_cpu->H); gb_cpu->cycles += 4;}
void SWAP_L(void) { printf("Called %s\n", __func__); instr_swap(gb_cpu->L); gb_cpu->cycles += 4;}
void SWAP_HLm(void) { printf("Called %s\n", __func__); }
void SWAP_A(void) { printf("Called %s\n", __func__); instr_swap(gb_cpu->A); gb_cpu->cycles += 4;}

void SRL_B(void) { printf("Called %s\n", __func__); instr_srl(*gb_cpu->B); gb_cpu->cycles += 4;}
void SRL_C(void) { printf("Called %s\n", __func__); instr_srl(*gb_cpu->C); gb_cpu->cycles += 4;}
void SRL_D(void) { printf("Called %s\n", __func__); instr_srl(*gb_cpu->D); gb_cpu->cycles += 4;}
void SRL_E(void) { printf("Called %s\n", __func__); instr_srl(*gb_cpu->E); gb_cpu->cycles += 4;}
void SRL_H(void) { printf("Called %s\n", __func__); instr_srl(*gb_cpu->H); gb_cpu->cycles += 4;}
void SRL_L(void) { printf("Called %s\n", __func__); instr_srl(*gb_cpu->L); gb_cpu->cycles += 4;}
void SRL_HLm(void) { printf("Called %s\n", __func__); }
void SRL_A(void) { printf("Called %s\n", __func__); instr_srl(*gb_cpu->A); gb_cpu->cycles += 4;}


void BIT_0_B(void) {
  printf("Called %s\n", __func__);
  instr_bit(0, gb_cpu->B);
}
void BIT_0_C(void) {
  printf("Called %s\n", __func__);
  instr_bit(0, gb_cpu->C);
}
void BIT_0_D(void) {
  printf("Called %s\n", __func__);
  instr_bit(0, gb_cpu->D);
}
void BIT_0_E(void) {
  printf("Called %s\n", __func__);
  instr_bit(0, gb_cpu->E);
}
void BIT_0_H(void) {
  printf("Called %s\n", __func__);
  instr_bit(0, gb_cpu->H);
}
void BIT_0_L(void) {
  printf("Called %s\n", __func__);
  instr_bit(0, gb_cpu->L);
}
void BIT_0_HLm(void) { printf("Called %s\n", __func__); }
void BIT_0_A(void) {
  printf("Called %s\n", __func__);
  instr_bit(0, gb_cpu->A);
}
void BIT_1_B(void) {
  printf("Called %s\n", __func__);
  instr_bit(1, gb_cpu->B);
}
void BIT_1_C(void) {
  printf("Called %s\n", __func__);
  instr_bit(1, gb_cpu->C);
}
void BIT_1_D(void) {
  printf("Called %s\n", __func__);
  instr_bit(1, gb_cpu->D);
}
void BIT_1_E(void) {
  printf("Called %s\n", __func__);
  instr_bit(1, gb_cpu->E);
}
void BIT_1_H(void) {
  printf("Called %s\n", __func__);
  instr_bit(1, gb_cpu->H);
}
void BIT_1_L(void) {
  printf("Called %s\n", __func__);
  instr_bit(1, gb_cpu->L);
}
void BIT_1_HLm(void) { printf("Called %s\n", __func__); }
void BIT_1_A(void) {
  printf("Called %s\n", __func__);
  instr_bit(1, gb_cpu->A);
}
void BIT_2_B(void) {
  printf("Called %s\n", __func__);
  instr_bit(2, gb_cpu->B);
}
void BIT_2_C(void) {
  printf("Called %s\n", __func__);
  instr_bit(2, gb_cpu->C);
}
void BIT_2_D(void) {
  printf("Called %s\n", __func__);
  instr_bit(2, gb_cpu->D);
}
void BIT_2_E(void) {
  printf("Called %s\n", __func__);
  instr_bit(2, gb_cpu->E);
}
void BIT_2_H(void) {
  printf("Called %s\n", __func__);
  instr_bit(2, gb_cpu->H);
}
void BIT_2_L(void) {
  printf("Called %s\n", __func__);
  instr_bit(2, gb_cpu->L);
}
void BIT_2_HLm(void) { printf("Called %s\n", __func__); }
void BIT_2_A(void) {
  printf("Called %s\n", __func__);
  instr_bit(2, gb_cpu->A);
}
void BIT_3_B(void) {
  printf("Called %s\n", __func__);
  instr_bit(3, gb_cpu->B);
}
void BIT_3_C(void) {
  printf("Called %s\n", __func__);
  instr_bit(3, gb_cpu->C);
}
void BIT_3_D(void) {
  printf("Called %s\n", __func__);
  instr_bit(3, gb_cpu->D);
}
void BIT_3_E(void) {
  printf("Called %s\n", __func__);
  instr_bit(3, gb_cpu->E);
}
void BIT_3_H(void) {
  printf("Called %s\n", __func__);
  instr_bit(3, gb_cpu->H);
}
void BIT_3_L(void) {
  printf("Called %s\n", __func__);
  instr_bit(3, gb_cpu->L);
}
void BIT_3_HLm(void) { printf("Called %s\n", __func__); }
void BIT_3_A(void) {
  printf("Called %s\n", __func__);
  instr_bit(3, gb_cpu->A);
}
void BIT_4_B(void) {
  printf("Called %s\n", __func__);
  instr_bit(4, gb_cpu->B);
}
void BIT_4_C(void) {
  printf("Called %s\n", __func__);
  instr_bit(4, gb_cpu->C);
}
void BIT_4_D(void) {
  printf("Called %s\n", __func__);
  instr_bit(4, gb_cpu->D);
}
void BIT_4_E(void) {
  printf("Called %s\n", __func__);
  instr_bit(4, gb_cpu->E);
}
void BIT_4_H(void) {
  printf("Called %s\n", __func__);
  instr_bit(4, gb_cpu->H);
}
void BIT_4_L(void) {
  printf("Called %s\n", __func__);
  instr_bit(4, gb_cpu->L);
}
void BIT_4_HLm(void) { printf("Called %s\n", __func__); }
void BIT_4_A(void) {
  printf("Called %s\n", __func__);
  instr_bit(4, gb_cpu->A);
}
void BIT_5_B(void) {
  printf("Called %s\n", __func__);
  instr_bit(5, gb_cpu->B);
}
void BIT_5_C(void) {
  printf("Called %s\n", __func__);
  instr_bit(5, gb_cpu->C);
}
void BIT_5_D(void) {
  printf("Called %s\n", __func__);
  instr_bit(5, gb_cpu->D);
}
void BIT_5_E(void) {
  printf("Called %s\n", __func__);
  instr_bit(5, gb_cpu->E);
}
void BIT_5_H(void) {
  printf("Called %s\n", __func__);
  instr_bit(5, gb_cpu->H);
}
void BIT_5_L(void) {
  printf("Called %s\n", __func__);
  instr_bit(5, gb_cpu->L);
}
void BIT_5_HLm(void) { printf("Called %s\n", __func__); }
void BIT_5_A(void) {
  printf("Called %s\n", __func__);
  instr_bit(5, gb_cpu->A);
}
void BIT_6_B(void) {
  printf("Called %s\n", __func__);
  instr_bit(6, gb_cpu->B);
}
void BIT_6_C(void) {
  printf("Called %s\n", __func__);
  instr_bit(6, gb_cpu->C);
}
void BIT_6_D(void) {
  printf("Called %s\n", __func__);
  instr_bit(6, gb_cpu->D);
}
void BIT_6_E(void) {
  printf("Called %s\n", __func__);
  instr_bit(6, gb_cpu->E);
}
void BIT_6_H(void) {
  printf("Called %s\n", __func__);
  instr_bit(6, gb_cpu->H);
}
void BIT_6_L(void) {
  printf("Called %s\n", __func__);
  instr_bit(6, gb_cpu->L);
}
void BIT_6_HLm(void) { printf("Called %s\n", __func__); }
void BIT_6_A(void) {
  printf("Called %s\n", __func__);
  instr_bit(6, gb_cpu->A);
}
void BIT_7_B(void) {
  printf("Called %s\n", __func__);
  instr_bit(7, gb_cpu->B);
}
void BIT_7_C(void) {
  printf("Called %s\n", __func__);
  instr_bit(7, gb_cpu->C);
}
void BIT_7_D(void) {
  printf("Called %s\n", __func__);
  instr_bit(7, gb_cpu->D);
}
void BIT_7_E(void) {
  printf("Called %s\n", __func__);
  instr_bit(7, gb_cpu->E);
}

void BIT_7_H(void) {
  printf("Called %s\n", __func__);
  instr_bit(7, gb_cpu->H);
}
void BIT_7_L(void) {
  printf("Called %s\n", __func__);
  instr_bit(7, gb_cpu->L);
}
void BIT_7_HLm(void) { printf("Called %s\n", __func__); }
void BIT_7_A(void) {
  printf("Called %s\n", __func__);
  instr_bit(7, gb_cpu->A);
}

void RES_0_B(void) { printf("Called %s\n", __func__); }
void RES_0_C(void) { printf("Called %s\n", __func__); }
void RES_0_D(void) { printf("Called %s\n", __func__); }
void RES_0_E(void) { printf("Called %s\n", __func__); }
void RES_0_H(void) { printf("Called %s\n", __func__); }
void RES_0_L(void) { printf("Called %s\n", __func__); }
void RES_0_HLm(void) { printf("Called %s\n", __func__); }
void RES_0_A(void) { printf("Called %s\n", __func__); }
void RES_1_B(void) { printf("Called %s\n", __func__); }
void RES_1_C(void) { printf("Called %s\n", __func__); }
void RES_1_D(void) { printf("Called %s\n", __func__); }
void RES_1_E(void) { printf("Called %s\n", __func__); }
void RES_1_H(void) { printf("Called %s\n", __func__); }
void RES_1_L(void) { printf("Called %s\n", __func__); }
void RES_1_HLm(void) { printf("Called %s\n", __func__); }
void RES_1_A(void) { printf("Called %s\n", __func__); }
void RES_2_B(void) { printf("Called %s\n", __func__); }
void RES_2_C(void) { printf("Called %s\n", __func__); }
void RES_2_D(void) { printf("Called %s\n", __func__); }
void RES_2_E(void) { printf("Called %s\n", __func__); }
void RES_2_H(void) { printf("Called %s\n", __func__); }
void RES_2_L(void) { printf("Called %s\n", __func__); }
void RES_2_HLm(void) { printf("Called %s\n", __func__); }
void RES_2_A(void) { printf("Called %s\n", __func__); }
void RES_3_B(void) { printf("Called %s\n", __func__); }
void RES_3_C(void) { printf("Called %s\n", __func__); }
void RES_3_D(void) { printf("Called %s\n", __func__); }
void RES_3_E(void) { printf("Called %s\n", __func__); }
void RES_3_H(void) { printf("Called %s\n", __func__); }
void RES_3_L(void) { printf("Called %s\n", __func__); }
void RES_3_HLm(void) { printf("Called %s\n", __func__); }
void RES_3_A(void) { printf("Called %s\n", __func__); }
void RES_4_B(void) { printf("Called %s\n", __func__); }
void RES_4_C(void) { printf("Called %s\n", __func__); }
void RES_4_D(void) { printf("Called %s\n", __func__); }
void RES_4_E(void) { printf("Called %s\n", __func__); }
void RES_4_H(void) { printf("Called %s\n", __func__); }
void RES_4_L(void) { printf("Called %s\n", __func__); }
void RES_4_HLm(void) { printf("Called %s\n", __func__); }
void RES_4_A(void) { printf("Called %s\n", __func__); }
void RES_5_B(void) { printf("Called %s\n", __func__); }
void RES_5_C(void) { printf("Called %s\n", __func__); }
void RES_5_D(void) { printf("Called %s\n", __func__); }
void RES_5_E(void) { printf("Called %s\n", __func__); }
void RES_5_H(void) { printf("Called %s\n", __func__); }
void RES_5_L(void) { printf("Called %s\n", __func__); }
void RES_5_HLm(void) { printf("Called %s\n", __func__); }
void RES_5_A(void) { printf("Called %s\n", __func__); }
void RES_6_B(void) { printf("Called %s\n", __func__); }
void RES_6_C(void) { printf("Called %s\n", __func__); }
void RES_6_D(void) { printf("Called %s\n", __func__); }
void RES_6_E(void) { printf("Called %s\n", __func__); }
void RES_6_H(void) { printf("Called %s\n", __func__); }
void RES_6_L(void) { printf("Called %s\n", __func__); }
void RES_6_HLm(void) { printf("Called %s\n", __func__); }
void RES_6_A(void) { printf("Called %s\n", __func__); }
void RES_7_B(void) { printf("Called %s\n", __func__); }
void RES_7_C(void) { printf("Called %s\n", __func__); }
void RES_7_D(void) { printf("Called %s\n", __func__); }
void RES_7_E(void) { printf("Called %s\n", __func__); }
void RES_7_H(void) { printf("Called %s\n", __func__); }
void RES_7_L(void) { printf("Called %s\n", __func__); }
void RES_7_HLm(void) { printf("Called %s\n", __func__); }
void RES_7_A(void) { printf("Called %s\n", __func__); }

void SET_0_B(void) { printf("Called %s\n", __func__); }
void SET_0_C(void) { printf("Called %s\n", __func__); }
void SET_0_D(void) { printf("Called %s\n", __func__); }
void SET_0_E(void) { printf("Called %s\n", __func__); }
void SET_0_H(void) { printf("Called %s\n", __func__); }
void SET_0_L(void) { printf("Called %s\n", __func__); }
void SET_0_HLm(void) { printf("Called %s\n", __func__); }
void SET_0_A(void) { printf("Called %s\n", __func__); }
void SET_1_B(void) { printf("Called %s\n", __func__); }
void SET_1_C(void) { printf("Called %s\n", __func__); }
void SET_1_D(void) { printf("Called %s\n", __func__); }
void SET_1_E(void) { printf("Called %s\n", __func__); }
void SET_1_H(void) { printf("Called %s\n", __func__); }
void SET_1_L(void) { printf("Called %s\n", __func__); }
void SET_1_HLm(void) { printf("Called %s\n", __func__); }
void SET_1_A(void) { printf("Called %s\n", __func__); }
void SET_2_B(void) { printf("Called %s\n", __func__); }
void SET_2_C(void) { printf("Called %s\n", __func__); }
void SET_2_D(void) { printf("Called %s\n", __func__); }
void SET_2_E(void) { printf("Called %s\n", __func__); }
void SET_2_H(void) { printf("Called %s\n", __func__); }
void SET_2_L(void) { printf("Called %s\n", __func__); }
void SET_2_HLm(void) { printf("Called %s\n", __func__); }
void SET_2_A(void) { printf("Called %s\n", __func__); }
void SET_3_B(void) { printf("Called %s\n", __func__); }
void SET_3_C(void) { printf("Called %s\n", __func__); }
void SET_3_D(void) { printf("Called %s\n", __func__); }
void SET_3_E(void) { printf("Called %s\n", __func__); }
void SET_3_H(void) { printf("Called %s\n", __func__); }
void SET_3_L(void) { printf("Called %s\n", __func__); }
void SET_3_HLm(void) { printf("Called %s\n", __func__); }
void SET_3_A(void) { printf("Called %s\n", __func__); }
void SET_4_B(void) { printf("Called %s\n", __func__); }
void SET_4_C(void) { printf("Called %s\n", __func__); }
void SET_4_D(void) { printf("Called %s\n", __func__); }
void SET_4_E(void) { printf("Called %s\n", __func__); }
void SET_4_H(void) { printf("Called %s\n", __func__); }
void SET_4_L(void) { printf("Called %s\n", __func__); }
void SET_4_HLm(void) { printf("Called %s\n", __func__); }
void SET_4_A(void) { printf("Called %s\n", __func__); }
void SET_5_B(void) { printf("Called %s\n", __func__); }
void SET_5_C(void) { printf("Called %s\n", __func__); }
void SET_5_D(void) { printf("Called %s\n", __func__); }
void SET_5_E(void) { printf("Called %s\n", __func__); }
void SET_5_H(void) { printf("Called %s\n", __func__); }
void SET_5_L(void) { printf("Called %s\n", __func__); }
void SET_5_HLm(void) { printf("Called %s\n", __func__); }
void SET_5_A(void) { printf("Called %s\n", __func__); }
void SET_6_B(void) { printf("Called %s\n", __func__); }
void SET_6_C(void) { printf("Called %s\n", __func__); }
void SET_6_D(void) { printf("Called %s\n", __func__); }
void SET_6_E(void) { printf("Called %s\n", __func__); }
void SET_6_H(void) { printf("Called %s\n", __func__); }
void SET_6_L(void) { printf("Called %s\n", __func__); }
void SET_6_HLm(void) { printf("Called %s\n", __func__); }
void SET_6_A(void) { printf("Called %s\n", __func__); }
void SET_7_B(void) { printf("Called %s\n", __func__); }
void SET_7_C(void) { printf("Called %s\n", __func__); }
void SET_7_D(void) { printf("Called %s\n", __func__); }
void SET_7_E(void) { printf("Called %s\n", __func__); }
void SET_7_H(void) { printf("Called %s\n", __func__); }
void SET_7_L(void) { printf("Called %s\n", __func__); }
void SET_7_HLm(void) { printf("Called %s\n", __func__); }
void SET_7_A(void) { printf("Called %s\n", __func__); }

void (*prefix_cb[256])(void) = {
    RLC_B,   RLC_C,   RLC_D,   RLC_E,   RLC_H,   RLC_L,   RLC_HLm,   RLC_A,
    RRC_B,   RRC_C,   RRC_D,   RRC_E,   RRC_H,   RRC_L,   RRC_HLm,   RRC_A,
    RL_B,    RL_C,    RL_D,    RL_E,    RL_H,    RL_L,    RL_HLm,    RL_A,
    RR_B,    RR_C,    RR_D,    RR_E,    RR_H,    RR_L,    RR_HLm,    RR_A,
    SLA_B,   SLA_C,   SLA_D,   SLA_E,   SLA_H,   SLA_L,   SLA_HLm,   SLA_A,
    SRA_B,   SRA_C,   SRA_D,   SRA_E,   SRA_H,   SRA_L,   SRA_HLm,   SRA_A,
    SWAP_B,  SWAP_C,  SWAP_D,  SWAP_E,  SWAP_H,  SWAP_L,  SWAP_HLm,  SWAP_A,
    SRL_B,   SRL_C,   SRL_D,   SRL_E,   SRL_H,   SRL_L,   SRL_HLm,   SRL_A,
    BIT_0_B, BIT_0_C, BIT_0_D, BIT_0_E, BIT_0_H, BIT_0_L, BIT_0_HLm, BIT_0_A,
    BIT_1_B, BIT_1_C, BIT_1_D, BIT_1_E, BIT_1_H, BIT_1_L, BIT_1_HLm, BIT_1_A,
    BIT_2_B, BIT_2_C, BIT_2_D, BIT_2_E, BIT_2_H, BIT_2_L, BIT_2_HLm, BIT_2_A,
    BIT_3_B, BIT_3_C, BIT_3_D, BIT_3_E, BIT_3_H, BIT_3_L, BIT_3_HLm, BIT_3_A,
    BIT_4_B, BIT_4_C, BIT_4_D, BIT_4_E, BIT_4_H, BIT_4_L, BIT_4_HLm, BIT_4_A,
    BIT_5_B, BIT_5_C, BIT_5_D, BIT_5_E, BIT_5_H, BIT_5_L, BIT_5_HLm, BIT_5_A,
    BIT_6_B, BIT_6_C, BIT_6_D, BIT_6_E, BIT_6_H, BIT_6_L, BIT_6_HLm, BIT_6_A,
    BIT_7_B, BIT_7_C, BIT_7_D, BIT_7_E, BIT_7_H, BIT_7_L, BIT_7_HLm, BIT_7_A,

    RES_0_B, RES_0_C, RES_0_D, RES_0_E, RES_0_H, RES_0_L, RES_0_HLm, RES_0_A,
    RES_1_B, RES_1_C, RES_1_D, RES_1_E, RES_1_H, RES_1_L, RES_1_HLm, RES_1_A,
    RES_2_B, RES_2_C, RES_2_D, RES_2_E, RES_2_H, RES_2_L, RES_2_HLm, RES_2_A,
    RES_3_B, RES_3_C, RES_3_D, RES_3_E, RES_3_H, RES_3_L, RES_3_HLm, RES_3_A,
    RES_4_B, RES_4_C, RES_4_D, RES_4_E, RES_4_H, RES_4_L, RES_4_HLm, RES_4_A,
    RES_5_B, RES_5_C, RES_5_D, RES_5_E, RES_5_H, RES_5_L, RES_5_HLm, RES_5_A,
    RES_6_B, RES_6_C, RES_6_D, RES_6_E, RES_6_H, RES_6_L, RES_6_HLm, RES_6_A,
    RES_7_B, RES_7_C, RES_7_D, RES_7_E, RES_7_H, RES_7_L, RES_7_HLm, RES_7_A,

    SET_0_B, SET_0_C, SET_0_D, SET_0_E, SET_0_H, SET_0_L, SET_0_HLm, SET_0_A,
    SET_1_B, SET_1_C, SET_1_D, SET_1_E, SET_1_H, SET_1_L, SET_1_HLm, SET_1_A,
    SET_2_B, SET_2_C, SET_2_D, SET_2_E, SET_2_H, SET_2_L, SET_2_HLm, SET_2_A,
    SET_3_B, SET_3_C, SET_3_D, SET_3_E, SET_3_H, SET_3_L, SET_3_HLm, SET_3_A,
    SET_4_B, SET_4_C, SET_4_D, SET_4_E, SET_4_H, SET_4_L, SET_4_HLm, SET_4_A,
    SET_5_B, SET_5_C, SET_5_D, SET_5_E, SET_5_H, SET_5_L, SET_5_HLm, SET_5_A,
    SET_6_B, SET_6_C, SET_6_D, SET_6_E, SET_6_H, SET_6_L, SET_6_HLm, SET_6_A,
    SET_7_B, SET_7_C, SET_7_D, SET_7_E, SET_7_H, SET_7_L, SET_7_HLm, SET_7_A};
