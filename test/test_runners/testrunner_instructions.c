#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Instructions)
{
  RUN_TEST_CASE(Instructions, adc);
  RUN_TEST_CASE(Instructions, add_A);
  RUN_TEST_CASE(Instructions, add_HL);
  RUN_TEST_CASE(Instructions, add_SP);
  RUN_TEST_CASE(Instructions, and);
  RUN_TEST_CASE(Instructions, bit);
}
