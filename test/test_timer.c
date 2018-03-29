#include "timer.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Timer);


TEST_SETUP(Timer)
{
}

TEST_TEAR_DOWN(Timer)
{
}

TEST(Timer, init)
{
    timer_t t;
    t.div =44;
    timer_init(&t);
    TEST_ASSERT_EQUAL(t.div, 0);
}

TEST(Timer, run_len)
{
    timer_t t;
    timer_init(&t);
    for(uint8_t i =0; i < 32; i++) timer_run(&t);
    TEST_ASSERT_EQUAL(32, t.div);
}
