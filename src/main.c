#include "memory.h"
#include "CPU.h"
#include "op_codes.h"
#include <stdio.h>

int main(int argc, const char * argv[])
{
  uint8_t exit = 2;
  uint8_t step = 0;

  // DEBUG_PRINTF("GB emulator...\n");
  CPU_init(gb_cpu);
  memory_init(memory);
  memory_load_cart(memory);
  gb_cpu->PC = 0x100;
  for(;;)
  {
    //fetch
    uint8_t op = memory_read8(memory, gb_cpu->PC);  //read OP code
    DEBUG_PRINTF("0x%04X:0x%02X::", gb_cpu->PC, op);
    gb_cpu->PC += 1; //inc pc

    //execute
    op_codes[op]();
    if(0)// if(gb_cpu->PC == 0x00B || step == 1) //gb_cpu->cycles - old_pc >= 20)
    {
          step =1;
          scanf("%d", &exit);
          if(exit == 0) break;
    }
    DEBUG_PRINTF("PC: 0x%04X\nSP: 0x%04X\n\nAF:0x%04X\nBC:0x%04X\nDE:0x%04X\nHL:0x%04X\n", gb_cpu->PC,gb_cpu->SP,*gb_cpu->AF,*gb_cpu->BC,*gb_cpu->DE,*gb_cpu->HL);
    DEBUG_PRINTF("A:0x%02X - F:0x%02X\nB:0x%02X - C:0x%02X\nD:0x%02X - E:0x%02X\nH:0x%02X - L:0x%02X\n",*gb_cpu->A,*gb_cpu->F, *gb_cpu->B,*gb_cpu->C,*gb_cpu->D,*gb_cpu->E,*gb_cpu->H,*gb_cpu->L);
  }
  return 0;
}
