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
    TEST_ASSERT_EQUAL(0, 1);
}
