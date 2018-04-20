#include "timer.h"
#include "CPU.h"
#include "memory.h"

#define DIVIDER_MASK (0b00000011)
#define ENABLE_MASK  (0b00000100)

static uint16_t tac_masks[4] = {1024, 16, 64, 256};

static timer_t t;
timer_t * timer = &t;


void timer_init(timer_t *t){
    t->div = 0;
    t->control = &memory->memory[TAC];
    t->counter = &memory->memory[TIMA];
    t->modulo = &memory->memory[TMA];
    t->prev_div = 0;
}

void timer_reset(timer_t *t) {
    t->div = 0;
    t->prev_div =0;
}

void timer_set(timer_t *t, const uint8_t time) {
    *t->counter = time;
}

void timer_run(timer_t *t) {
    uint8_t increment = 0;
    uint8_t divider = *t->control & DIVIDER_MASK;
    uint16_t timer_mask = tac_masks[divider];

    //todo Safe wrapping of DIV
    t->div++; //DIV is always incremented

    if((*t->control & ENABLE_MASK) != ENABLE_MASK) return; //timer not enabled

    //timer control check if counter should increment
    uint16_t div = t->div & timer_mask;
    increment = div != t->prev_div;
    t->prev_div = div;


    //inc TIMA or handle overflow
    if(*t->counter == 0xFF && increment) {
        *t->counter = *t->modulo; //reload timer
        //interrupt flag set
        CPU_set_interrupt(gb_cpu, INT_TMR);
    }
    else if(increment) {
        //increment counter based on div and scaler
        *t->counter++;

    }

}
