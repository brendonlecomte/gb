#include "timer.h"

static uint16_t tac_masks[4] = {0x01<<3, 0x01<<5, 0x01<<7, 0x01<<9};

void timer_init(timer_t* t){
    t->div = 0;
}

void timer_reset(timer_t* t) {

}

void timer_run(timer_t* t) {
    t->div++;
}
