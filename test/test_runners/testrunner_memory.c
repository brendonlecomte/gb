#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Memory)
{
  RUN_TEST_CASE(Memory, init);
  RUN_TEST_CASE(Memory, read8);
  RUN_TEST_CASE(Memory, read16);
  RUN_TEST_CASE(Memory, write8);
  RUN_TEST_CASE(Memory, write16);
  RUN_TEST_CASE(Memory, inboot);
}
