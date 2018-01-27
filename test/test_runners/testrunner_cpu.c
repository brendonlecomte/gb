#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(processor)
{
  RUN_TEST_CASE(processor, init);
  RUN_TEST_CASE(processor, read8);
  RUN_TEST_CASE(processor, read16);
  RUN_TEST_CASE(processor, write8);
  RUN_TEST_CASE(processor, write16);
  RUN_TEST_CASE(processor, pop);
  RUN_TEST_CASE(processor, push);
  RUN_TEST_CASE(processor, ptrs);
  RUN_TEST_CASE(processor, flags);
}
