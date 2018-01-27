#ifndef CPU_H
#define CPU_H

#include <stdbool.h>
#include <stdint.h>

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

#define CARRY_FLAG (0x10)
#define HALF_CARRY_FLAG (0x20)
#define SUBTRACT_FLAG (0x40)
#define ZERO_FLAG (0x80)

typedef struct {
  /*
    SP - Stack Pointer
    PC - Progam Counter
    */
  uint16_t SP, PC;

  /*
    8Bit Registers in the CPU
  */
  struct {
    uint8_t A, B, C, D, E, F, H, L;
  } registers;

  uint8_t *A, *B, *C, *D, *E, *F, *H, *L;
  uint16_t AF, BC, DE, HL;
  /*
  Timing
  */
  uint32_t cycles;
} CPU_t;

extern CPU_t *gb_cpu;

void CPU_init(CPU_t *cpu);
void CPU_set_flag(uint8_t flag);
void CPU_clear_flag(uint8_t flag);
bool CPU_check_flag(uint8_t flag);

uint16_t CPU_stack_pop(void);
void CPU_stack_push(uint16_t val);

uint16_t CPU_read_AF(void);
uint16_t CPU_read_BC(void);
uint16_t CPU_read_DE(void);
uint16_t CPU_read_HL(void);
void CPU_write_AF(uint16_t val);
void CPU_write_BC(uint16_t val);
void CPU_write_DE(uint16_t val);
void CPU_write_HL(uint16_t val);

uint8_t CPU_read_A(void);
uint8_t CPU_read_B(void);
uint8_t CPU_read_C(void);
uint8_t CPU_read_D(void);
uint8_t CPU_read_E(void);
uint8_t CPU_read_H(void);
uint8_t CPU_read_L(void);
void CPU_write_A(uint8_t val);
void CPU_write_B(uint8_t val);
void CPU_write_C(uint8_t val);
void CPU_write_D(uint8_t val);
void CPU_write_E(uint8_t val);
void CPU_write_H(uint8_t val);
void CPU_write_L(uint8_t val);
#endif // CPU_H
