#include "gb_timer.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Timer);

static gb_timer_t t;

TEST_SETUP(Timer)
{
    gb_timer_init(&t);
}

TEST_TEAR_DOWN(Timer)
{
}

TEST(Timer, init)
{
    t.div =44;
    gb_timer_init(&t);
    TEST_ASSERT_EQUAL(t.div, 0);
}

TEST(Timer, run_len)
{

    t.div = 0;
    *t.counter = 0;
    t.prev_div = 0;
    *t.control = GB_TIMER_ENABLE | GB_TIMER_DIV_16;
    for(uint16_t i = 0; i < 16; i++) gb_timer_run(&t);
    TEST_ASSERT_EQUAL(1, *t.counter);

    t.div = 0;
    *t.counter = 0;
    t.prev_div = 0;
    *t.control = GB_TIMER_ENABLE | GB_TIMER_DIV_1024;
    for(uint16_t i = 0; i < 1024; i++) gb_timer_run(&t);
    TEST_ASSERT_EQUAL(1, *t.counter);

    t.div = 0;
    t.prev_div = 0;
    *t.counter = 0;
    *t.control = GB_TIMER_ENABLE | GB_TIMER_DIV_64;
    for(uint16_t i = 0; i < 64; i++) gb_timer_run(&t);
    TEST_ASSERT_EQUAL(1, *t.counter);

    t.div = 0;
    t.prev_div = 0;
    *t.counter = 0;
    *t.control = GB_TIMER_ENABLE | GB_TIMER_DIV_256;
    for(uint16_t i = 0; i < 256; i++) gb_timer_run(&t);
    TEST_ASSERT_EQUAL(1, *t.counter);
}

TEST(Timer, reload)
{
    *t.counter = 0xFE;
    *t.modulo = 0xAA;
    *t.control = GB_TIMER_ENABLE | GB_TIMER_DIV_16;
    t.div = 0x10;
    gb_timer_run(&t);
    TEST_ASSERT_EQUAL(0xFF, *t.counter);

    t.div = 0xFF;
    gb_timer_run(&t);
    TEST_ASSERT_EQUAL(0xAA, *t.counter);
}

TEST(Timer, enable)
{
    *t.control = GB_TIMER_DIV_16;
    for(uint16_t i = 0; i < 32; i++) gb_timer_run(&t);
    TEST_ASSERT_EQUAL(0, *t.counter);

    *t.control |= GB_TIMER_ENABLE;
    for(uint16_t i = 0; i < 16; i++) gb_timer_run(&t);
    TEST_ASSERT_EQUAL(1, *t.counter);

}
