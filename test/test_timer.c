#include "timer.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Timer);

static timer_t t;

TEST_SETUP(Timer)
{
    timer_init(&t);
}

TEST_TEAR_DOWN(Timer)
{
}

TEST(Timer, init)
{
    t.div =44;
    timer_init(&t);
    TEST_ASSERT_EQUAL(t.div, 0);
}

TEST(Timer, run_len)
{

    t.div = 0;
    *t.counter = 0;
    t.prev_div = 0;
    *t.control = TIMER_ENABLE | TIMER_DIV_16;
    for(uint16_t i = 0; i < 16; i++) timer_run(&t);
    TEST_ASSERT_EQUAL(1, *t.counter);

    t.div = 0;
    *t.counter = 0;
    t.prev_div = 0;
    *t.control = TIMER_ENABLE | TIMER_DIV_1024;
    for(uint16_t i = 0; i < 1024; i++) timer_run(&t);
    TEST_ASSERT_EQUAL(1, *t.counter);

    t.div = 0;
    t.prev_div = 0;
    *t.counter = 0;
    *t.control = TIMER_ENABLE | TIMER_DIV_64;
    for(uint16_t i = 0; i < 64; i++) timer_run(&t);
    TEST_ASSERT_EQUAL(1, *t.counter);

    t.div = 0;
    t.prev_div = 0;
    *t.counter = 0;
    *t.control = TIMER_ENABLE | TIMER_DIV_256;
    for(uint16_t i = 0; i < 256; i++) timer_run(&t);
    TEST_ASSERT_EQUAL(1, *t.counter);
}

TEST(Timer, reload)
{
    *t.counter = 0xFE;
    *t.modulo = 0xAA;
    *t.control = TIMER_ENABLE | TIMER_DIV_16;
    t.div = 0x10;
    timer_run(&t);
    TEST_ASSERT_EQUAL(0xFF, *t.counter);

    t.div = 0xFF;
    timer_run(&t);
    TEST_ASSERT_EQUAL(0xAA, *t.counter);
}

TEST(Timer, enable)
{
    *t.control = TIMER_DIV_16;
    for(uint16_t i = 0; i < 32; i++) timer_run(&t);
    TEST_ASSERT_EQUAL(0, *t.counter);

    *t.control |= TIMER_ENABLE;
    for(uint16_t i = 0; i < 16; i++) timer_run(&t);
    TEST_ASSERT_EQUAL(1, *t.counter);

}
