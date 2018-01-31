#include "memory.h"
#include "CPU.h"
#include "op_codes.h"
#include <stdio.h>


int main(int argc, const char * argv[])
{
  uint8_t exit = 1;
  uint8_t old_pc = 0;
  printf("GB emulator...\n");
  CPU_init(gb_cpu);
  memory_init(memory);
  for(;;)
  {
    //fetch
    uint8_t op = memory_read8(memory, gb_cpu->PC);  //read OP code
    printf("0x%04X:0x%02X::", gb_cpu->PC, op);
    gb_cpu->PC += 1; //inc pc

    //execute
    op_codes[op]();
    if(op == 0x00 || gb_cpu->HL < 0x8001) //gb_cpu->cycles - old_pc >= 20)
    {
        old_pc = gb_cpu->cycles;

        scanf("%d", &exit);
        if(exit == 0) break;
    }
    printf("PC: 0x%04X\nSP: 0x%04X\n\nAF:0x%04X\nBC:0x%04X\nDE:0x%04X\nHL:0x%04X\n", gb_cpu->PC,gb_cpu->SP,*gb_cpu->AF,*gb_cpu->BC,*gb_cpu->DE,*gb_cpu->HL);
    printf("A:0x%02X - F:0x%02X\nB:0x%02X - C:0x%02X\nD:0x%02X - E:0x%02X\nH:0x%02X - L:0x%02X\n",*gb_cpu->A,*gb_cpu->F, *gb_cpu->B,*gb_cpu->C,*gb_cpu->D,*gb_cpu->E,*gb_cpu->H,*gb_cpu->L);
  }
  return 0;
}
