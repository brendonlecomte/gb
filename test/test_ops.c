#include "op_codes.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Ops);


TEST_SETUP(Ops)
{
}

TEST_TEAR_DOWN(Ops)
{
}

TEST(Ops, init)
{

    TEST_ASSERT_EQUAL(0x0000, *gb_cpu->AF);
    TEST_ASSERT_EQUAL(0x0000, *gb_cpu->BC);
    TEST_ASSERT_EQUAL(0x0000, *gb_cpu->DE);
    TEST_ASSERT_EQUAL(0x0000, *gb_cpu->HL);

}
