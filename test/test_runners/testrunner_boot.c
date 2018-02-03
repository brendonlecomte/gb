#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Boot)
{
  RUN_TEST_CASE(Boot, zero_vram);
  RUN_TEST_CASE(Boot, audio);
}
