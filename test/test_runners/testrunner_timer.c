#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Timer)
{
  RUN_TEST_CASE(Timer, init);
  RUN_TEST_CASE(Timer, run_len);
  RUN_TEST_CASE(Timer, reload);
  RUN_TEST_CASE(Timer, enable);
}
