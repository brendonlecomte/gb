#include "memory.h"
#include "memory_locations.h"
#include "CPU.h"
#include "op_codes.h"
#include "emulator.h"
#include "ppu.h"
#include "gb_timer.h"

void emu_init(void) {
  CPU_init(gb_cpu);
  memory_init(memory);
  ppu_init();
  gb_timer_init(gb_timer);
}

bool pause = false;
bool stepping = false;
bool trace_started = true;

void emu_pause(void) {
    if(pause) pause = false;
    else pause = true;
}

void emu_execute(void) {
  if(gb_cpu->cycles <= 0 && !gb_cpu->halt)  //done enough "clocks"
  {
      if(gb_cpu->PC == 0x100) trace_started = true;

      if(gb_cpu->int_to_enable) { //EI was the last instruction
        gb_cpu->ime = 1;
        gb_cpu->int_to_enable = 0;
      }

      //fetch
      uint8_t op = memory_read8(memory, gb_cpu->PC);  //read OP code
      gb_cpu->PC += 1; //inc pc

      //execute
      op_codes[op]();

      if(trace_started) {
          TRACE_PRINTF("PC:0x%04X OP:0x%02X AF:0x%04X BC:0x%04X DE:0x%04X HL:0x%04X SP:0x%04X ", gb_cpu->PC, op, *gb_cpu->AF,*gb_cpu->BC,*gb_cpu->DE,*gb_cpu->HL, gb_cpu->SP);
          TRACE_PRINTF("IME:0x%d IF:0x%02X IE:0x%02X ", gb_cpu->ime, *(uint8_t *)gb_cpu->int_flags, *(uint8_t *)gb_cpu->int_enable);
          TRACE_PRINTF("LCDC:0x%02X LCDS:0x%02X ", memory_read8(LCDC), memory_read8(STAT));
          TRACE_PRINTF("\n");
      }
  }

  //timers
  gb_timer_run(gb_timer);

  //Graphics
  ppu_run();

  //interrupts
  CPU_handle_interrupt(gb_cpu);

  //cycles run at 4Mhz
  if(!pause && gb_cpu->cycles > 0) gb_cpu->cycles -= 1;
}

void emu_end(void) {
  ppu_close();
}
