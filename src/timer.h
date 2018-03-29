#include <stdint.h>
#include <stdbool.h>

typedef struct {
  uint8_t unused:5;
  bool enable:1;
  uint8_t divider:2;
} timer_control_t;

typedef struct {
    uint16_t div;
    uint8_t key;
    uint8_t* counter;
    uint8_t* modulo;
    timer_control_t* control;
} timer_t;

void timer_init(timer_t* t);
void timer_reset(timer_t* t);
void timer_run(timer_t* t);
