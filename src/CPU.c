#include "CPU.h"
#include "memory.h"

CPU_t _cpu;
CPU_t *gb_cpu = &_cpu;

void CPU_init(CPU_t *cpu) {
  cpu->PC = 0x0000;
  cpu->SP = 0xFFFE;

  //set pointers
  cpu->AF = &cpu->registers.AF._16;
  cpu->BC = &cpu->registers.BC._16;
  cpu->DE = &cpu->registers.DE._16;
  cpu->HL = &cpu->registers.HL._16;
  //
  cpu->A = (uint8_t*)&cpu->registers.AF._8[1];
  cpu->B = (uint8_t*)&cpu->registers.BC._8[1];
  cpu->D = (uint8_t*)&cpu->registers.DE._8[1];
  cpu->H = (uint8_t*)&cpu->registers.HL._8[1];

  cpu->F = (uint8_t*)&cpu->registers.AF._8[0];
  cpu->C = (uint8_t*)&cpu->registers.BC._8[0];
  cpu->E = (uint8_t*)&cpu->registers.DE._8[0];
  cpu->L = (uint8_t*)&cpu->registers.HL._8[0];

  *cpu->AF = 0x0000;
  *cpu->BC = 0;
  *cpu->DE = 0;
  *cpu->HL = 0;
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

void CPU_set_flag(const uint8_t flg) {
    static uint8_t f;
    f = *_cpu.F;
    f = f | flg;
    *_cpu.F = f;
}

void CPU_clear_flag(const uint8_t flg) {
    static uint8_t f;
    f = *_cpu.F;
    f  &= ~flg;
    *_cpu.F = f;
}

bool CPU_check_flag(uint8_t flg) {
    return ((*_cpu.F & flg) == flg);
}
