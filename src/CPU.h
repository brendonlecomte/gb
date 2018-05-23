#ifndef CPU_H
#define CPU_H

#include <stdbool.h>
#include <stdint.h>
#include "debug.h"

/*
Bit 4 represents the carry flag.  It is set when a carry from bit 7 is produced
in arithmetical instructions.  Otherwise it is cleared. Bit 5 represents the
half-carry flag.  It is set when a carry from bit 3 is produced in arithmetical
instructions.  Otherwise it is cleared.  It has a very common use, that is, for
the DAA (decimal adjust) instruction.  Games used it extensively for displaying
decimal values on the screen. Bit 6 represents the subtract flag.  When the
instruction is a subtraction this bit is set.  Otherwise (the instruction is an
addition) it is cleared. Bit 7 represents the zero flag.  It is set when the
instruction results in a value of 0.  Otherwise (result different to 0) it is
cleared.
*/


#define CARRY_FLAG  (0x10)
#define HALF_CARRY_FLAG  (0x20)
#define SUBTRACT_FLAG  (0x40)
#define ZERO_FLAG  (0x80)

typedef enum {
   INT_UNUSED,
   INT_JOYPAD=4,
   INT_SERIAL=3,
   INT_TMR =2 ,
   INT_LCD_STAT = 1,
   INT_V_BLANK = 0
} interrupts_t;

typedef struct {
  uint8_t v_blank:1;
  uint8_t lcd_stat:1;
  uint8_t tmr:1;
  uint8_t serial:1;
  uint8_t joypad:1;
  uint8_t unused:3;
} int_reg_t;

typedef union reg_u {
    uint16_t  _16;
    uint8_t   _8[2];
} reg_t;

typedef struct {
  /*
    SP - Stack Pointer
    PC - Progam Counter
    */
  uint16_t SP, PC;

  // 8Bit Registers in the CPU
  struct {
       reg_t AF;
       reg_t BC;
       reg_t DE;
       reg_t HL;
  } registers;

  uint8_t *A, *B, *C, *D, *E, *F, *H, *L;
  uint16_t *AF, *BC, *DE, *HL;

  bool ime; //master interrupt, cpu controlled
  int_reg_t *int_flags;
  int_reg_t *int_enable;
  bool int_to_enable;

  //  Timing
  int32_t cycles;
  bool halt;
} CPU_t;

extern CPU_t *gb_cpu;

void CPU_init(CPU_t *cpu);
void CPU_enable_interrupt(CPU_t *cpu, interrupts_t interrupt);
void CPU_handle_interrupt(CPU_t *cpu);
void CPU_set_interrupt(CPU_t *cpu, interrupts_t interrupt);
void CPU_set_flag(const uint8_t flg, uint8_t val);
bool CPU_check_flag(const uint8_t flg);

uint16_t CPU_stack_pop(void);
void CPU_stack_push(uint16_t val);

#endif // CPU_H
