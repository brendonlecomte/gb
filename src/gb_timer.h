#include <stdint.h>
#include <stdbool.h>

#define GB_TIMER_ENABLE    (0x04)
#define GB_TIMER_DIV_1024  (0x00)
#define GB_TIMER_DIV_256   (0x03)
#define GB_TIMER_DIV_64    (0x02)
#define GB_TIMER_DIV_16    (0x01)

typedef struct {
  uint8_t divider:2;
  bool enable:1;
  uint8_t unused:5;
} gb_timer_control_t;

typedef struct {
    uint16_t div;
    uint16_t prev_div;
    uint8_t key;
    uint8_t *counter;
    uint8_t *modulo;
    uint8_t *control;
} gb_timer_t;

extern gb_timer_t * gb_timer;

void gb_timer_init(gb_timer_t* t);
void gb_timer_reset(gb_timer_t* t);
void gb_timer_run(gb_timer_t* t);
void gb_timer_set(gb_timer_t *t, const uint8_t time);
