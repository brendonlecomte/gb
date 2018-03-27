#include "memory.h"
#include "CPU.h"
#include "op_codes.h"
#include "emulator.h"
#include "ppu.h"

void emu_init(void) {
  CPU_init(gb_cpu);
  memory_init(memory);
  memory_load_cart(memory);
  ppu_init();
}

bool pause = false;
bool stepping = false;
bool trace_started = true;

void emu_pause(void) {
    if(pause) pause = false;
    else pause = true;
}

void emu_execute(void) {
  if(gb_cpu->cycles <= 0)  //done enough "clocks"
  {
      if(gb_cpu->PC == 0x100) trace_started = true;

      //fetch
      uint8_t op = memory_read8(memory, gb_cpu->PC);  //read OP code
      // DEBUG_PRINTF("OP: 0x%04X:0x%02X::", gb_cpu->PC, op);
      gb_cpu->PC += 1; //inc pc

      //execute
      op_codes[op]();

      if(trace_started) TRACE_PRINTF("0x%04X: 0x%02X -> AF:0x%04X BC:0x%04X DE: 0x%04X HL: 0x%04X SP:0x%04X\n", gb_cpu->PC, op, *gb_cpu->AF,*gb_cpu->BC,*gb_cpu->DE,*gb_cpu->HL, gb_cpu->SP);

      // if(gb_cpu->PC == 0x100 && !stepping) stepping = true;
      // if(stepping) pause = true;
  }
  //interrupts
  CPU_handle_interrupt(gb_cpu);

  //timers

  //sound

  //Graphics
  ppu_run();

  if(!pause) gb_cpu->cycles -= 1;
}

void emu_end(void) {
  ppu_close();
}
