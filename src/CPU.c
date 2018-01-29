#include "CPU.h"
#include "memory.h"

CPU_t _cpu;
CPU_t *gb_cpu = &_cpu;

void CPU_init(CPU_t *cpu) {
  cpu->PC = 0x0000;
  cpu->SP = 0xFFFE;

  // Register AF set to 0x01 for GB
  cpu->AF = 0x0000;
  cpu->BC = 0;
  cpu->HL = 0;

  cpu->A = (uint8_t*)&cpu->AF;
  cpu->F = cpu->A + 1;
  *cpu->F = 0x01;

  cpu->B = (uint8_t*)&cpu->BC;
  cpu->C = cpu->B + 1;

  cpu->D = (uint8_t*)&cpu->DE;
  cpu->E = cpu->D + 1;

  cpu->H = (uint8_t*)&cpu->HL;
  cpu->L = cpu->H + 1;
}

void CPU_stack_push(uint16_t val) {
  _cpu.SP -= 2;
  memory_write16(memory, _cpu.SP, val);
}

uint16_t CPU_stack_pop(void) {
  uint16_t t = memory_read16(memory, _cpu.SP);
  _cpu.SP += 2;
  return t;
}

void CPU_set_flag(uint8_t flag) { *_cpu.F = *_cpu.F | flag; }

void CPU_clear_flag(uint8_t flag) { *_cpu.F = *_cpu.F & ~flag; }

bool CPU_check_flag(uint8_t flag) { return (!!(*_cpu.F & flag));
}

uint16_t CPU_read_AF(void) { return _cpu.AF; }

uint16_t CPU_read_BC(void) { return _cpu.BC; }

uint16_t CPU_read_DE(void) { return _cpu.DE; }

uint16_t CPU_read_HL(void) { return _cpu.HL; }

void CPU_write_AF(uint16_t val) {
  _cpu.AF = (val & 0xFF00); // canot write flags in this manner
}

void CPU_write_BC(uint16_t val) { _cpu.BC = val; }

void CPU_write_DE(uint16_t val) { _cpu.DE = val; }

void CPU_write_HL(uint16_t val) { _cpu.HL = val; }

uint8_t CPU_read_A(void) { return *_cpu.A; }
uint8_t CPU_read_B(void) { return *_cpu.B; }
uint8_t CPU_read_C(void) { return *_cpu.C;}
uint8_t CPU_read_D(void) { return *_cpu.D; }
uint8_t CPU_read_E(void) { return *_cpu.E; }
uint8_t CPU_read_H(void) { return *_cpu.H; }
uint8_t CPU_read_L(void) { return *_cpu.L; }

void CPU_write_A(uint8_t val) {
  *_cpu.A = val;
}
void CPU_write_B(uint8_t val) {
  *_cpu.B = val;
}
void CPU_write_C(uint8_t val) {
  *_cpu.C = val;
}
void CPU_write_D(uint8_t val) {
 *_cpu.D = val;
}
void CPU_write_E(uint8_t val) {
 *_cpu.E = val;
}
void CPU_write_H(uint8_t val) {
  *_cpu.H = val;
}
void CPU_write_L(uint8_t val) {
 *_cpu.L = val;
}
