#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Instructions) {
  RUN_TEST_CASE(Instructions, adc);
  RUN_TEST_CASE(Instructions, add8);
  RUN_TEST_CASE(Instructions, add_HL);
  RUN_TEST_CASE(Instructions, add_SP);
  RUN_TEST_CASE(Instructions, and);
  RUN_TEST_CASE(Instructions, bit);
  RUN_TEST_CASE(Instructions, call_n);
  RUN_TEST_CASE(Instructions, ccf);
  RUN_TEST_CASE(Instructions, cpl);
  RUN_TEST_CASE(Instructions, inc)
  RUN_TEST_CASE(Instructions, inc_nn);
  // RUN_TEST_CASE(Instructions, jp);
  // RUN_TEST_CASE(Instructions, jp_hl);
  // RUN_TEST_CASE(Instructions, jr);
  // RUN_TEST_CASE(Instructions, load_an);
  // RUN_TEST_CASE(Instructions, load_na);
  // RUN_TEST_CASE(Instructions, xor);
  // RUN_TEST_CASE(Instructions, srl);
}
