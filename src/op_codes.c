#include "CPU.h"
#include "instructions.h"
#include "memory.h"
#include "op_codes.h"

// 0x00 NOP
void NOP(void) { gb_cpu->cycles += 4; }

//0x01 LD BC, d16
void LD_BC_d16(void) {
  CPU_write_BC(memory_read16(memory, gb_cpu->PC));
  gb_cpu->PC += 2;
  gb_cpu->cycles += 12;
}

//0x02 LD (BC), A
void LD_mBC_A(void) {
    // memory_write8(memory, uint16_t addr, uint8_t val)
    gb_cpu->cycles += 8;
}

//0x03 INC BC
void INC_BC(void) {
    CPU_write_BC(CPU_read_BC() + 1);
    gb_cpu->cycles += 8;
}

//0x04 INC B
void INC_B(void) {

    gb_cpu->cycles += 4;
}

/*
void (void) {
  uint8_t n = memory_read8(memory, gb_cpu->PC);
  gb_cpu->PC += 1;
  uint16_t n = memory_read16(memory, gb_cpu->PC);
  gb_cpu->PC += 2;
  instr_  (gb_cpu, );
  gp->cylces += X;
}

*/

void(*op_codes[256]) = {
    NOP,
    LD_BC_d16,
    INC_BC,

};
