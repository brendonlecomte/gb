#include "CPU.h"
#include "memory.h"

CPU_t _cpu;
CPU_t *gb_cpu = &_cpu;

void CPU_init(CPU_t *cpu) {
  cpu->PC = 0x0100;
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

  cpu->ime = 0;
  cpu->interrupt_flags = (int_reg_t*)&memory->memory[0xFF0F];
  cpu->interrupt_enable = (int_reg_t*)&memory->memory[0xFFFF];
}

void CPU_handle_interrupt(CPU_t *cpu) {
  CPU_stack_push(cpu->PC); // push PC, 2cycles
  // PC = 0x0040, 0x0048, 0x0050, 0x0058, 0x0060;
  uint16_t rst_vector;
  //faux priority
  if(cpu->interrupt_flags->joypad) rst_vector = 0x0060;
  if(cpu->interrupt_flags->serial) rst_vector = 0x0058;
  if(cpu->interrupt_flags->tmr) rst_vector = 0x0050;
  if(cpu->interrupt_flags->lcd_stat) rst_vector = 0x0048;
  if(cpu->interrupt_flags->v_blank) rst_vector = 0x0040;
  cpu->PC = rst_vector;
  cpu->cycles += 5;
}

void CPU_set_interrupt(CPU_t *cpu, interrupts_t interrupt) {
  cpu->ime = 0;
  switch(interrupt){
    case INT_V_BLANK:
      cpu->interrupt_flags->v_blank = 1;
      break;
    case INT_LCD_STAT:
      cpu->interrupt_flags->lcd_stat = 1;
      break;
    case INT_TMR:
      cpu->interrupt_flags->tmr = 1;
      break;
    case INT_SERIAL:
      cpu->interrupt_flags->serial = 1;
      break;
    case INT_JOYPAD:
      cpu->interrupt_flags->joypad = 1;
      break;
    default:
      // assert(0);
      break;
  }
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
