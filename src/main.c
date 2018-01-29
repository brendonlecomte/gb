#include "memory.h"
#include "CPU.h"
#include "op_codes.h"
#include <stdio.h>


int main(int argc, const char * argv[])
{
  uint8_t exit = 1;
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
    if(gb_cpu->PC > 0x10 )
    {scanf("%d", &exit);}
    if(exit == 0) break;

  }
  return 0;
}
