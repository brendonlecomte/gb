#include "CPU.h"


void CPU_init(CPU_t* cpu)
{
  cpu->PC = 0x100;
  cpu->SP = 0xFFFE;

  //Register AF set to 0x01 for GB
  cpu->registers.A = 0;
  cpu->registers.B = 0;
  cpu->registers.C = 0;
  cpu->registers.D = 0;
  cpu->registers.E = 0;
  cpu->registers.F = 1;
  cpu->registers.H = 0;
  cpu->registers.L = 0;
}
