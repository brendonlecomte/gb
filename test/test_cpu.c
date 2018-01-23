#include "CPU.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(processor);


TEST_SETUP(processor)
{

}

TEST_TEAR_DOWN(processor)
{
}

TEST(processor, init)
{
  CPU_t cpu;
  CPU_init(&cpu);
  TEST_ASSERT_EQUAL(cpu.registers.A, 0);
  TEST_ASSERT_EQUAL(cpu.registers.B, 0);
  TEST_ASSERT_EQUAL(cpu.registers.C, 0);
  TEST_ASSERT_EQUAL(cpu.registers.D, 0);
  TEST_ASSERT_EQUAL(cpu.registers.E, 0);
  TEST_ASSERT_EQUAL(cpu.registers.F, 1);
  TEST_ASSERT_EQUAL(cpu.registers.H, 0);
  TEST_ASSERT_EQUAL(cpu.registers.L, 0);

  TEST_ASSERT_EQUAL(cpu.PC, 0x100);
  TEST_ASSERT_EQUAL(cpu.SP, 0xFFFE);

}
