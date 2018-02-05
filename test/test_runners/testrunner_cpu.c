#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(processor)
{
  RUN_TEST_CASE(processor, init);
  RUN_TEST_CASE(processor, poppush);
  RUN_TEST_CASE(processor, ints);
  RUN_TEST_CASE(processor, ptrs);
  RUN_TEST_CASE(processor, flags);
}
