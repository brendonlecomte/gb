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
  RUN_TEST_CASE(Instructions, dec_nn);
  RUN_TEST_CASE(Instructions, di);
  RUN_TEST_CASE(Instructions, ei);
  RUN_TEST_CASE(Instructions, jp);
  RUN_TEST_CASE(Instructions, jp_hl);
  RUN_TEST_CASE(Instructions, jr);
  RUN_TEST_CASE(Instructions, load_ab);
  RUN_TEST_CASE(Instructions, load_ab16);

  RUN_TEST_CASE(Instructions, or);
  RUN_TEST_CASE(Instructions, push);
  RUN_TEST_CASE(Instructions, pop);
  RUN_TEST_CASE(Instructions, res);
  RUN_TEST_CASE(Instructions, ret);

  RUN_TEST_CASE(Instructions, rl);
  RUN_TEST_CASE(Instructions, rlc);
  RUN_TEST_CASE(Instructions, rr);
  RUN_TEST_CASE(Instructions, rrc);

  RUN_TEST_CASE(Instructions, rst);
  RUN_TEST_CASE(Instructions, sbc);
  RUN_TEST_CASE(Instructions, sub);
  RUN_TEST_CASE(Instructions, swap);
  RUN_TEST_CASE(Instructions, xor);
  RUN_TEST_CASE(Instructions, srl);
}
