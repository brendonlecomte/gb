#include "CPU.h"
#include "instructions.h"
#include "memory.h"
#include "op_codes.h"
#include <stdio.h>

// 0x00 NOP
void NOP(void) { gb_cpu->cycles += 4; }

//0x01 LD BC, d16
void LD_BC_d16(void) {
  gb_cpu->BC = memory_read16(memory, gb_cpu->PC);
  gb_cpu->PC += 2;
  gb_cpu->cycles += 12;
}

//0x02 LD (BC), A
void LD_mBC_A(void) {
    gb_cpu->BC = *gb_cpu->A;
    gb_cpu->cycles += 8;
}

//0x03 INC BC
void INC_BC(void) {
    CPU_write_BC(CPU_read_BC() + 1);
    gb_cpu->cycles += 8;
}

//0x04 INC B
void INC_B(void) {
    instr_inc_n(gb_cpu->B);
    gb_cpu->cycles += 4;
}

//0x05 DEC B
void DEC_B(void) {
  instr_dec_n(gb_cpu->B);
  gb_cpu->cycles += 4;
}

//0x06 LD B, d8
void LD_B_d8(void) {
  uint8_t d8 = memory_read8(memory, gb_cpu->PC);
  instr_load_ab(gb_cpu->B, d8);
  gb_cpu->PC += 1;
  gb_cpu->cycles += 8;
}

// 0x07 RLCA
void RLCA(void) {
  instr_rlc(gb_cpu->A);
  gb_cpu->cycles += 4;
}

// 0x08 LD (a16), SP
void LD_a16_SP(void) {
  instr_load_ab16(&gb_cpu->SP, memory_read16(memory, gb_cpu->PC));
  gb_cpu->PC += 2;
  gb_cpu->cycles += 20;
}

// 0x09 ADD HL, BC
void ADD_HL_BC(void) {
  instr_add_HL(&gb_cpu->HL, gb_cpu->BC);
  gb_cpu->cycles += 4;
}

// 0x0A LD A, (BC)
void LD_A_BC(void) {
  instr_load_ab(gb_cpu->A, memory_read8(memory, gb_cpu->BC));
  gb_cpu->cycles += 8;
}

// 0x0B DEC BC
void DEC_BC(void) {
  instr_dec_nn(&gb_cpu->BC);
  gb_cpu->cycles += 8;
}

// 0x0C INC C
void INC_C(void) {
  instr_inc_n(gb_cpu->C);
  gb_cpu->cycles += 4;
}

// 0x0D DEC C
void DEC_C(void) {
  instr_dec_n(gb_cpu->C);
  gb_cpu->cycles += 4;
}

// 0x0E LD C, d8
void LD_C_d8(void) {
  instr_load_ab(gb_cpu->C, memory_read8(memory, gb_cpu->PC));
  gb_cpu->SP += 1;
  gb_cpu->cycles += 4;
}

// 0x0F RRCA
void RRCA(void) {
  instr_rrc(gb_cpu->A);
  gb_cpu->cycles += 4;
}

// 0x10 STOP 0
void STOP(void) {
  instr_stop();
  gb_cpu->PC += 2;
  gb_cpu->cycles += 4;
}

// 0x11 NAME
void LD_DE_d16(void) {
  instr_load_ab16(&gb_cpu->DE, memory_read16(memory, gb_cpu->PC));
  gb_cpu->PC += 2;
  gb_cpu->cycles += 12;
}

// 0x12 LD (DE) A
void LD_DE_A(void) {
  // instr_load_ab(memory_write8(memory, ))
  gb_cpu->cycles += 8;
}

// 0x13 INC DE
// 1 8
void INC_DE(void) {
  gb_cpu->cycles += 8;
}

// 0x14 INC_D
// 1 4
void INC_D(void) {
  gb_cpu->cycles += 4;
}

// 0x15 DEC D
// 1 4
void DEC_D(void) {
  gb_cpu->cycles += 4;
}

// 0x16 LD D, d8
// 2 8
void LD_D_d8(void) {
  gb_cpu->cycles += 8;
}

// 0x17 RLA
// 1 4
void RLA(void) {
  gb_cpu->cycles += 4;
}

// 0x18 JR r8
// 2 12
void JR_r8(void) {
  gb_cpu->cycles += 12;
}

// 0x19 ADD HL, DE
// 1 8
void ADD_HL_DE(void) {
  gb_cpu->cycles += 8;
}

// 0x1A LD A, (DE)
// 1 8
void LD_A_DE(void) {
  gb_cpu->cycles += 8;
}

// 0x1B DEC DE
// 1 8
void DEC_DE(void) {
  gb_cpu->cycles += 8;
}

// 0x1C INC_E
// 1 4
void INC_E(void) {
  gb_cpu->cycles += 4;
}

// 0x1D DEC E
// 1 4
void DEC_E(void) {
  gb_cpu->cycles += 4;
}

// 0x1E LD e, d8
// 1 4
void LD_E_d8(void) {
  gb_cpu->cycles += 4;
}

// 0x1F RRA
// 1 4
void RRA(void) {
  gb_cpu->cycles += 4;
}


// 0x2....
// JR NZ,r8
// 2  12/8
void JR_NZ_r8(void) {

}

// LD HL,d16
// 3  12
void LD_HL_d16(void) {

}

//LD (HL+),A
// 1  8
void LD_HLp_A(void) {

}

// INC HL
// 1  8
void INC_HL(void) {

}

// INC H
// 1  4
void INC_H(void) {

}

// DEC H
// 1  4
void DEC_H(void) {

}

// LD H,d8
// 2  8
void LD_H_d8(void) {}

// DAA
// 1  4
void DAA(void) {}

// JR Z,r8
// 2  12/8
void JR_Z_r8(void) {}

// ADD HL,HL
// 1  8
void ADD_HL_HL(void) {}

// LD A,(HL+)
// 1  8
void LD_A_HLp(void) {}

// DEC HL
// 1  8
void DEC_HL(void) {}

// INC L
// 1  4
void INC_L(void) {}

// DEC L
// 1  4
void DEC_L(void) {}

// LD L,d8
// 2  8
void LD_L_d8(void) {}

// CPL
// 1  4
void CPL(void) {}

//0x3....
// JR NC,r8
// 2  12/8
void JR_NC_r8(void) {

}

// LD SP,d16
// 3  12
void LD_SP_d16(void) {

}

// LD (HL-),A
// 1  8
void LD_HLs_A(void) {

}

// INC SP
// 1  8
void INC_SP(void) {

}

// INC (HL)
// 1  12
void INC_aHL(void){
}

// DEC (HL)
// 1  12
void DEC_aHL(void) {

}

// LD (HL),d8
// 2  12
void LD_mHL_d8(void) {

}

// SCF
// 1  4
void SCF(void) {

}

// JR C,r8
// 2  12/8
void JR_C_r8(void) {

}

// ADD HL,SP
// 1  8
void ADD_HL_SP(void) {

}

// LD A,(HL-)
// 1  8
void LD_A_HLs(void) {

}

// DEC SP
// 1  8
void DEC_SP(void) {

}

// INC A
// 1  4
void INC_A(void) {

}

// DEC A
// 1  4
void DEC_A(void) {

}

// LD A,d8
// 2  8
void LD_A_d8(void) {

}

// CCF
// 1  4
void CCF(void) {

}


// 0x4...
// LD B,B
// 1  4
void LD_B_B(void) {}

// LD B,C
// 1  4
void LD_B_C(void) {}

// LD B,D
// 1  4
void LD_B_D(void) {}

// LD B,E
// 1  4
void LD_B_E(void) {}

// LD B,H
// 1  4
void LD_B_H(void) {}

// LD B,L
// 1  4
void LD_B_L(void) {}

// LD B,(HL)
// 1  8
void LD_B_HLm(void) {}

// LD B,A
// 1  4
void LD_B_A(void) {}

// LD C,B
// 1  4
void LD_C_B(void) {}

// LD C,C
// 1  4
void LD_C_C(void) {}

// LD C,D
// 1  4
void LD_C_D(void) {}

// LD C,E
// 1  4
void LD_C_E(void) {}

// LD C,H
// 1  4
void LD_C_H(void) {}

// LD C,L
// 1  4
void LD_C_L(void) {}

// LD C,(HL)
// 1  8
void LD_C_HLm(void) {}

// LD C,A
// 1  4
void LD_C_A(void) {}

//0x5...
// LD D,B
// 1  4
void LD_D_B(void) {}

// LD D,C
// 1  4
void LD_D_C(void) {}

// LD D,D
// 1  4
void LD_D_D(void) {}

// LD D,E
// 1  4
void LD_D_E(void) {}

// LD D,H
// 1  4
void LD_D_H(void) {}

// LD D,L
// 1  4
void LD_D_L(void) {}

// LD D,(HL)
// 1  8
void LD_D_HLm(void) {}

// LD D,A
// 1  4
void LD_D_A(void) {}
// LD E,B
// 1  4
void LD_E_B(void) {}
// LD E,C
// 1  4
void LD_E_C(void) {}
// LD E,D
// 1  4
void LD_E_D(void) {}
// LD E,E
// 1  4
void LD_E_E(void) {}
// LD E,H
// 1  4
void LD_E_H(void) {}
// LD E,L
// 1  4
void LD_E_L(void) {}
// LD E,(HL)
// 1  8
void LD_E_HLm(void) {}
// LD E,A
// 1  4
void LD_E_A(void) {}

//0x6....
// LD H,B
// 1  4
void LD_H_B(void) {}

// LD H,C
// 1  4
void LD_H_C(void) {}
// LD H,D
// 1  4
void LD_H_D(void) {}

// LD H,E
// 1  4
void LD_H_E(void) {}
// LD H,H
// 1  4
void LD_H_H(void) {}
// LD H,L
// 1  4
void LD_H_L(void) {}
// LD H,(HL)
// 1  8
void LD_H_HLm(void) {}
// LD H,A
// 1  4
void LD_H_A(void) {}
// LD L,B
// 1  4
void LD_L_B(void) {}
// LD L,C
// 1  4
void LD_L_C(void) {}
// LD L,D
// 1  4
void LD_L_D(void) {}
// LD L,E
// 1  4
void LD_L_E(void) {}
// LD L,H
// 1  4
void LD_L_H(void) {}
// LD L,L
// 1  4
void LD_L_L(void) {}
// LD L,(HL)
// 1  8
void LD_L_HLm(void) {}
// LD L,A
// 1  4
void LD_L_A(void) {}

//0x7...
// LD (HL),B
// 1  8
void LD_HLm_B(void) {}
// LD (HL),C
// 1  8
void LD_HLm_C(void) {}
// LD (HL),D
// 1  8
void LD_HLm_D(void) {}
// LD (HL),E
// 1  8
void LD_HLm_E(void) {}
// LD (HL),H
// 1  8
void LD_HLm_H(void) {}
// LD (HL),L
// 1  8
void LD_HLm_L(void) {}
// HALT
// 1  4
void HALT(void) {}
// LD (HL),A
// 1  8
void LD_HLm_A(void) {}
// LD A,B
// 1  4
void LD_A_B(void) {}
// LD A,C
// 1  4
void LD_A_C(void) {}
// LD A,D
// 1  4
void LD_A_D(void) {}
// LD A,E
// 1  4
void LD_A_E(void) {}
// LD A,H
// 1  4
void LD_A_H(void) {}
// LD A,L
// 1  4
void LD_A_L(void) {}
// LD A,(HL)
// 1  8
void LD_A_HLm(void) {}
// LD A,A
// 1  4
void LD_A_A(void) {}

//0x8...
// ADD A,B
// 1  4
void ADD_A_B(void) {}
// ADD A,C
// 1  4
void ADD_A_C(void) {}
// ADD A,D
// 1  4
void ADD_A_D(void) {}
// ADD A,E
// 1  4
void ADD_A_E(void) {}
// ADD A,H
// 1  4
void ADD_A_H(void) {}
// ADD A,L
// 1  4
void ADD_A_L(void) {}
// ADD A,(HL)
// 1  8
void ADD_A_HLm(void) {}
// ADD A,A
// 1  4
void ADD_A_A(void) {}
// ADC A,B
// 1  4
void ADC_A_B(void) {}
// ADC A,C
// 1  4
void ADC_A_C(void) {}
// ADC A,D
// 1  4
void ADC_A_D(void) {}
// ADC A,E
// 1  4
void ADC_A_E(void) {}
// ADC A,H
// 1  4
void ADC_A_H(void) {}
// ADC A,L
// 1  4
void ADC_A_L(void) {}
// ADC A,(HL)
// 1  8
void ADC_A_HLm(void) {}
// ADC A,A
// 1  4
void ADC_A_A(void) {}

// 0x9..
// SUB B
// 1  4
void SUB_B(void) {}
// SUB C
// 1  4
void SUB_C(void) {}
// SUB D
// 1  4
void SUB_D(void) {}
// SUB E
// 1  4
void SUB_E(void) {}
// SUB H
// 1  4
void SUB_H(void) {}
// SUB L
// 1  4
void SUB_L(void) {}
// SUB (HL)
// 1  8
void SUB_HLm(void) {}
// SUB A
// 1  4
void SUB_A(void) {}
// SBC A,B
// 1  4
void SBC_A_B(void) {}
// SBC A,C
// 1  4
void SBC_A_C(void) {}
// SBC A,D
// 1  4
void SBC_A_D(void) {}
// SBC A,E
// 1  4
void SBC_A_E(void) {}
// SBC A,H
// 1  4
void SBC_A_H(void) {}
// SBC A,L
// 1  4
void SBC_A_L(void) {}
// SBC A,(HL)
// 1  8
void SBC_A_HLm(void) {}
// SBC A,A
// 1  4
void SBC_A_A(void) {}

//0xA..
// AND B
// 1  4
void AND_B(void) {}
// AND C
// 1  4
void AND_C(void) {}
// AND D
// 1  4
void AND_D(void) {}
// AND E
// 1  4
void AND_E(void) {}
// AND H
// 1  4
void AND_H(void) {}
// AND L
// 1  4
void AND_L(void) {}
// AND (HL)
// 1  8
void AND_HLm(void) {}
// AND A
// 1  4
void AND_A(void) {}
// XOR B
// 1  4
void XOR_B(void) {}
// XOR C
// 1  4
void XOR_C(void) {}
// XOR D
// 1  4
void XOR_D(void) {}
// XOR E
// 1  4
void XOR_E(void) {}
// XOR H
// 1  4
void XOR_H(void) {}
// XOR L
// 1  4
void XOR_L(void) {}
// XOR (HL)
// 1  8
void XOR_HLm(void) {}
// XOR A
// 1  4
void XOR_A(void) {}

//0xB...
// OR B
// 1  4
void OR_B(void) {}
// OR C
// 1  4
void OR_C(void) {}
// OR D
// 1  4
void OR_D(void) {}
// OR E
// 1  4
void OR_E(void) {}
// OR H
// 1  4
void OR_H(void) {}
// OR L
// 1  4
void OR_L(void) {}
// OR (HL)
// 1  8
void OR_HLm(void) {}
// OR A
// 1  4
void OR_A(void) {}
// CP B
// 1  4
void CP_B(void) {}
// CP C
// 1  4
void CP_C(void) {}
// CP D
// 1  4
void CP_D(void) {}
// CP E
// 1  4
void CP_E(void) {}
// CP H
// 1  4
void CP_H(void) {}
// CP L
// 1  4
void CP_L(void) {}
// CP (HL)
// 1  8
void CP_HLm(void) {}
// CP A
// 1  4
void CP_A(void) {}

//0xC...
// RET NZ
// 1  20/8
void RET_NZ(void) {}
// POP BC
// 1  12
void POP_BC(void) {}
// JP NZ,a16
// 3  16/12
void JP_NZ_a16(void) {}
// JP a16
// 3  16
void JP_a16(void) {}
// CALL NZ,a16
// 3  24/12
void CALL_NZ_a16(void) {}
// PUSH BC
// 1  16
void PUSH_BC(void) {}
// ADD A,d8
// 2  8
void ADD_A_d8(void) {}
// RST 00H
// 1  16
void RST_00H(void) {}
// RET Z
// 1  20/8
void RET_Z(void) {}
// RET
// 1  16
void RET(void) {}
// JP Z,a16
// 3  16/12
void JP_Z_a16(void) {}
// PREFIX CB
// 1  4
void PREFIX_CB(void) {}
// CALL Z,a16
// 3  24/12
void CALL_Z_a16(void) {}
// CALL a16
// 3  24
void CALL_a16(void) {}
// ADC A,d8
// 2  8
void ADC_A_d8(void) {}
// RST 08H
// 1  16
void RST_08H(void) {}

// 0xD...
// RET NC
// 1  20/8
// POP DE
// 1  12
// JP NC,a16
// 3  16/12
// CALL NC,a16
// 3  24/12
// PUSH DE
// 1  16
// SUB d8
// 2  8
// RST 10H
// 1  16
// RET C
// 1  20/8
// RETI
// 1  16
// JP C,a16
// 3  16/12
// CALL C,a16
// 3  24/12
// SBC A,d8
// 2  8
// RST 18H
// 1  16

// 0xE..
// LDH (a8),A
// 2  12
// POP HL
// 1  12
// LD (C),A
// 2  8
// PUSH HL
// 1  16
// AND d8
// 2  8
// RST 20H
// 1  16
// ADD SP,r8
// 2  16
// JP (HL)
// 1  4
// LD (a16),A
// 3  16
// XOR d8
// 2  8
// RST 28H
// 1  16

//0xF....
// LDH A,(a8)
// 2  12
// POP AF
// 1  12
// LD A,(C)
// 2  8
// DI
// 1  4
// PUSH AF
// 1  16
// OR d8
// 2  8
// RST 30H
// 1  16
// LD HL,SP+r8
// 2  12
// LD SP,HL
// 1  8
// LD A,(a16)
// 3  16
// EI
// 1  4
// CP d8
// 2  8
// RST 38H
// 1  16


void no_op(void) {}

void(*op_codes[256]) = {
    //0x0...
    NOP,
    LD_BC_d16,
    INC_BC,
    INC_B,
    DEC_B,
    LD_B_d8,
    RLCA,
    LD_a16_SP,
    ADD_HL_BC,
    LD_A_BC,
    DEC_BC,
    INC_C,
    DEC_C,
    LD_C_d8,
    RRCA,

    //0x1..s
    STOP,
    LD_DE_d16,
    LD_DE_A,
    INC_DE,
    INC_D,
    DEC_D,
    LD_D_d8,
    RLA,
    JR_r8,
    ADD_HL_DE,
    LD_A_DE,
    DEC_DE,
    INC_E,
    DEC_E,
    LD_E_d8,
    RRA,

    //0x2..
    JR_NZ_r8,
    LD_HL_d16,
    LD_HLp_A,
    INC_HL,
    INC_H,
    DEC_H,
    LD_H_d8,
    DAA,
    JR_Z_r8,
    ADD_HL_HL,
    LD_A_HLp,
    DEC_HL,
    INC_L,
    DEC_L,
    LD_L_d8,
    CPL,

    //0x3..
    JR_NC_r8,
    LD_SP_d16,
    LD_HLs_A,
    INC_SP,
    INC_aHL,
    DEC_aHL,
    LD_mHL_d8,
    SCF,
    JR_C_r8,
    ADD_HL_SP,
    LD_A_HLs,
    DEC_SP,
    INC_A,
    DEC_A,
    LD_A_d8,
    CCF,

    //0x4..
    LD_B_B,
    LD_B_C,
    LD_B_D,
    LD_B_E,
    LD_B_H,
    LD_B_L,
    LD_B_HLm,
    LD_B_A,
    LD_C_B,
    LD_C_C,
    LD_C_D,
    LD_C_E,
    LD_C_H,
    LD_C_L,
    LD_C_HLm,
    LD_C_A,

    //0x5..
    LD_D_B,
    LD_D_C,
    LD_D_D,
    LD_D_E,
    LD_D_H,
    LD_D_L,
    LD_D_HLm,
    LD_D_A,
    LD_E_B,
    LD_E_C,
    LD_E_D,
    LD_E_E,
    LD_E_H,
    LD_E_L,
    LD_E_HLm,
    LD_E_A,

    //0x6..
    LD_H_B,
    LD_H_C,
    LD_H_D,
    LD_H_E,
    LD_H_H,
    LD_H_L,
    LD_H_HLm,
    LD_H_A,
    LD_L_B,
    LD_L_C,
    LD_L_D,
    LD_L_E,
    LD_L_H,
    LD_L_L,
    LD_L_HLm,
    LD_L_A,

    //0x7..
    LD_HLm_B,
    LD_HLm_C,
    LD_HLm_D,
    LD_HLm_E,
    LD_HLm_H,
    LD_HLm_L,
    HALT,
    LD_HLm_A,
    LD_A_B,
    LD_A_C,
    LD_A_D,
    LD_A_E,
    LD_A_H,
    LD_A_L,
    LD_A_HLm,
    LD_A_A,

    //0x8..
    ADD_A_B,
    ADD_A_C,
    ADD_A_D,
    ADD_A_E,
    ADD_A_H,
    ADD_A_L,
    ADD_A_HLm,
    ADD_A_A,
    ADC_A_B,
    ADC_A_C,
    ADC_A_D,
    ADC_A_E,
    ADC_A_H,
    ADC_A_L,
    ADC_A_HLm,
    ADC_A_A,

    //0x9..
    SUB_B,
    SUB_C,
    SUB_D,
    SUB_E,
    SUB_H,
    SUB_L,
    SUB_HLm,
    SUB_A,
    SBC_A_B,
    SBC_A_C,
    SBC_A_D,
    SBC_A_E,
    SBC_A_H,
    SBC_A_L,
    SBC_A_HLm,
    SBC_A_A,

    //0xA..
    AND_B,
    AND_C,
    AND_D,
    AND_E,
    AND_H,
    AND_L,
    AND_HLm,
    AND_A,
    XOR_B,
    XOR_C,
    XOR_D,
    XOR_E,
    XOR_H,
    XOR_L,
    XOR_HLm,
    XOR_A

    //0xB..
    OR_B,
    OR_C,
    OR_D,
    OR_E,
    OR_H,
    OR_L,
    OR_HLm,
    OR_A,
    CP_B,
    CP_C,
    CP_D,
    CP_E,
    CP_H,
    CP_L,
    CP_HLm,
    CP_A,

    //0xC..
    RET_NZ,
    POP_BC,
    JP_NZ_a16,
    JP_a16,
    CALL_NZ_a16,
    PUSH_BC,
    ADD_A_d8,
    RST_00H,
    RET_Z,
    RET,
    JP_Z_a16,
    PREFIX_CB,
    CALL_Z_a16,
    CALL_a16,
    ADC_A_d8,
    RST_08H,

    //0xD..

    //0xE..

    //0xF..

};
