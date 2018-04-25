#include <stdint.h>
#include <stdbool.h>

#define TIMER_ENABLE    (0x04)
#define TIMER_DIV_1024  (0x00)
#define TIMER_DIV_256   (0x03)
#define TIMER_DIV_64    (0x02)
#define TIMER_DIV_16    (0x01)

typedef struct {
  uint8_t divider:2;
  bool enable:1;
  uint8_t unused:5;
} timer_control_t;

typedef struct {
    uint16_t div;
    uint16_t prev_div;
    uint8_t key;
    uint8_t *counter;
    uint8_t *modulo;
    uint8_t *control;
} timer_t;

extern timer_t * timer;

void timer_init(timer_t* t);
void timer_reset(timer_t* t);
void timer_run(timer_t* t);
void timer_set(timer_t *t, const uint8_t time);
