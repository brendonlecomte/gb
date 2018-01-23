#include "instructions.h"
#include "CPU.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Instructions);


TEST_SETUP(Instructions)
{

}

TEST_TEAR_DOWN(Instructions)
{
}

TEST(Instructions, adc)
{
  //Register A + #
  uint8_t n = 10;
  CPU_t cpu;
  cpu.registers.A = 0;
  instr_adc(&cpu, n);
  TEST_ASSERT_NOT_EQUAL(0, cpu.registers.F & ZERO_FLAG);
  TEST_ASSERT_EQUAL(10 , cpu.registers.A);

  //Register A + other Reg
  cpu.registers.A = 0;
  cpu.registers.B = 10;
  instr_adc(&cpu, cpu.registers.B);
  TEST_ASSERT_EQUAL(10 , cpu.registers.A);

  //Register A + large number giving Carry
}
