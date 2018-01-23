#ifndef CPU_H
#define CPU_H

#include <stdint.h>


/*
Bit 4 represents the carry flag.  It is set when a carry from bit 7 is produced in arithmetical instructions.  Otherwise it is cleared.
Bit 5 represents the half-carry flag.  It is set when a carry from bit 3 is produced in arithmetical instructions.  Otherwise it is cleared.  It has a very common use, that is, for the DAA (decimal adjust) instruction.  Games used it extensively for displaying decimal values on the screen.
Bit 6 represents the subtract flag.  When the instruction is a subtraction this bit is set.  Otherwise (the instruction is an addition) it is cleared.
Bit 7 represents the zero flag.  It is set when the instruction results in a value of 0.  Otherwise (result different to 0) it is cleared.
*/

#define CARRY_FLAG      (0x10)
#define HALF_CARRY_FLAG (0x20)
#define SUBTRACT_FLAG   (0x40)
#define ZERO_FLAG       (0x80)

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

} CPU_t;

void CPU_init(CPU_t* cpu);

#endif //CPU_H
