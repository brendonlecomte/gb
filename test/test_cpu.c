#include "CPU.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(processor);

CPU_t *cpu;

TEST_SETUP(processor) {
  cpu = gb_cpu;
  CPU_init(gb_cpu);
}

TEST_TEAR_DOWN(processor) {}

TEST(processor, init) {
  TEST_ASSERT_EQUAL(*cpu->A, 0);
  TEST_ASSERT_EQUAL(*cpu->B, 0);
  TEST_ASSERT_EQUAL(*cpu->C, 0);
  TEST_ASSERT_EQUAL(*cpu->D, 0);
  TEST_ASSERT_EQUAL(*cpu->E, 0);
  TEST_ASSERT_EQUAL(*cpu->F, 0x01);
  TEST_ASSERT_EQUAL(*cpu->H, 0);
  TEST_ASSERT_EQUAL(*cpu->L, 0);

  TEST_ASSERT_EQUAL(cpu->PC, 0x0100);
  TEST_ASSERT_EQUAL(cpu->SP, 0xFFFE);
}

TEST(processor, ptrs)
{
    gb_cpu->AF = 0xAA55;
    TEST_ASSERT_EQUAL(0xAA, *cpu->F);
    TEST_ASSERT_EQUAL(0x55, *cpu->A);

    gb_cpu->BC = 0xAA55;
    TEST_ASSERT_EQUAL(0xAA, *cpu->C);
    TEST_ASSERT_EQUAL(0x55, *cpu->B);

    gb_cpu->DE = 0xAA55;
    TEST_ASSERT_EQUAL(0xAA, *cpu->E);
    TEST_ASSERT_EQUAL(0x55, *cpu->D);

    gb_cpu->HL = 0xAA55;
    TEST_ASSERT_EQUAL(0xAA, *cpu->L);
    TEST_ASSERT_EQUAL(0x55, *cpu->H);
}

TEST(processor, flags)
{
    CPU_set_flag(CARRY_FLAG);
    TEST_ASSERT_EQUAL(1, CPU_check_flag(CARRY_FLAG));

    CPU_init(gb_cpu);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));

    CPU_clear_flag(CARRY_FLAG);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));

    CPU_set_flag(HALF_CARRY_FLAG);
    TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
    CPU_clear_flag(HALF_CARRY_FLAG);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(HALF_CARRY_FLAG));

    CPU_set_flag(ZERO_FLAG);
    TEST_ASSERT_EQUAL(1, CPU_check_flag(ZERO_FLAG));
    CPU_clear_flag(ZERO_FLAG);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));

    CPU_set_flag(SUBTRACT_FLAG);
    TEST_ASSERT_EQUAL(1, CPU_check_flag(SUBTRACT_FLAG));
    CPU_clear_flag(SUBTRACT_FLAG);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
}

TEST(processor, write8)
{
  CPU_write_A(0x55);
  // TEST_ASSERT_EQUAL(0x5501, CPU_read_AF());
  CPU_write_B(0x55);
  TEST_ASSERT_EQUAL(0x0055, CPU_read_BC());
  CPU_write_C(0xAA);
  TEST_ASSERT_EQUAL(0xAA55, CPU_read_BC());
 }

TEST(processor, read8)
{
    CPU_write_D(0xCC);
    TEST_ASSERT_EQUAL(0xCC, CPU_read_D());
    TEST_ASSERT_EQUAL(0x00, CPU_read_E());
}

TEST(processor, write16)
{

    CPU_write_DE(0x5AA5);
    TEST_ASSERT_EQUAL(0x5AA5, CPU_read_DE());

    CPU_write_BC(0x5AA5);
    TEST_ASSERT_EQUAL(0x5AA5, CPU_read_BC());
}

TEST(processor, read16)
{
    CPU_write_HL(0xCC12);
    TEST_ASSERT_EQUAL(0x12, CPU_read_H());
    TEST_ASSERT_EQUAL(0xCC, CPU_read_L());
}

TEST(processor, pop)
{
    CPU_stack_push(0xCC12);
    TEST_ASSERT_EQUAL(0xFFFC, cpu->SP);
    // TEST_ASSERT_EQUAL(0xCC12, CPU_stack_pop());
}

TEST(processor, push)
{
    CPU_write_HL(0xCC12);
    TEST_ASSERT_EQUAL(0x12, CPU_read_H());
    TEST_ASSERT_EQUAL(0xCC, CPU_read_L());
}
