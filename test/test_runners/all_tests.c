#include "unity_fixture.h"

static void RunAllTests(void)
{
  RUN_TEST_GROUP(processor);
  RUN_TEST_GROUP(Instructions);
  RUN_TEST_GROUP(Memory);
  // RUN_TEST_GROUP(Boot);
  RUN_TEST_GROUP(Cart);
  RUN_TEST_GROUP(Timer);
  // RUN_TEST_GROUP(Ops);
}

int main(int argc, const char * argv[])
{
  return UnityMain(argc, argv, RunAllTests);
}
