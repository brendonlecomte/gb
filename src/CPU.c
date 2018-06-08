#include "CPU.h"
#include "memory.h"


CPU_t _cpu;
CPU_t *gb_cpu = &_cpu;

void CPU_init(CPU_t *cpu) {
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

#if BOOT_ROM
  cpu->PC = 0x0000;
  cpu->SP = 0xFFFE;
  *cpu->AF = 0x0000;
  *cpu->BC = 0;
  *cpu->DE = 0;
  *cpu->HL = 0;
#else
  cpu->PC = 0x0100;
  cpu->SP = 0xFFFE;
  *cpu->AF = 0x1180;
  *cpu->BC = 0x0000;
  *cpu->DE = 0xff56;
  *cpu->HL = 0x000d;
#endif

  cpu->ime = 0;
  cpu->int_flags = (int_reg_t*)&memory->memory[IF];
  cpu->int_enable = (int_reg_t*)&memory->memory[IE];
  cpu->halt = false;

}

void CPU_handle_interrupt(CPU_t *cpu) {
    if(*(uint8_t *)cpu->int_flags != 0x00 && cpu->halt) {
        cpu->halt = false;
    }
    if(cpu->ime) { //if interrupts are enabled, handle them
      // PC = 0x0040, 0x0048, 0x0050, 0x0058, 0x0060;
      uint16_t rst_vector = 0xAA55;
      //faux priority
      if(cpu->int_flags->joypad) {
          rst_vector = 0x0060;
          cpu->int_flags->joypad = 0;
      }
      else if(cpu->int_flags->serial && cpu->int_enable->serial) {
          rst_vector = 0x0058;
          cpu->int_flags->serial = 0;
      }
      else if(cpu->int_flags->tmr && cpu->int_enable->tmr) {
          rst_vector = 0x0050;
          cpu->int_flags->tmr = 0;
      }
      else if(cpu->int_flags->lcd_stat && cpu->int_enable->lcd_stat){
          rst_vector = 0x0048;
          cpu->int_flags->lcd_stat = 0;
      }
      else if(cpu->int_flags->v_blank && cpu->int_enable->v_blank) {
          rst_vector = 0x0040;
          cpu->int_flags->v_blank = 0;
      }
      if(rst_vector != 0xAA55) //interrupt detected
      {
        cpu->ime = 0;
        CPU_stack_push(cpu->PC); // push PC, 2 cycles
        cpu->PC = rst_vector;
        cpu->cycles += 20;
      }
    }
}

void CPU_enable_interrupt(CPU_t *cpu, interrupts_t interrupt) {
  switch(interrupt) {
    case INT_V_BLANK:
      cpu->int_enable->v_blank = 1;
      break;
    case INT_LCD_STAT:
      cpu->int_enable->lcd_stat = 1;
      break;
    case INT_TMR:
      cpu->int_enable->tmr = 1;
      break;
    case INT_SERIAL:
      cpu->int_enable->serial = 1;
      break;
    case INT_JOYPAD:
      cpu->int_enable->joypad = 1;
      break;
    default:
      // assert(0); //catch mistakes
      break;
  }
}

void CPU_set_interrupt(CPU_t *cpu, interrupts_t interrupt) {
  switch(interrupt){
    case INT_V_BLANK:
      if(cpu->int_enable->v_blank) cpu->int_flags->v_blank = 1;
      break;
    case INT_LCD_STAT:
      if(cpu->int_enable->lcd_stat) cpu->int_flags->lcd_stat = 1;
      break;
    case INT_TMR:
      if(cpu->int_enable->tmr) cpu->int_flags->tmr = 1;
      break;
    case INT_SERIAL:
      if(cpu->int_enable->serial) cpu->int_flags->serial = 1;
      break;
    case INT_JOYPAD:
      if(cpu->int_enable->joypad) cpu->int_flags->joypad = 1;
      break;
    default:
      // assert(0); //catch mistakes
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

void CPU_set_flag(const uint8_t flg, uint8_t val)
{
    static uint8_t f;
    f = *_cpu.F;
    if(val) f = f | flg; //set
    else f = f & ~flg; //set
    *_cpu.F = f;
}

void CPU_clear_all_flags(void) {
  *_cpu.F = 0;
}

bool CPU_check_flag(uint8_t flg) {
    return ((*_cpu.F & flg) == flg);
}
