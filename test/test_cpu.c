#include "CPU.h"
#include "memory.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(processor);

CPU_t *cpu;

TEST_SETUP(processor) {
  cpu = gb_cpu;
  CPU_init(gb_cpu);
  memory_init(memory);
}

TEST_TEAR_DOWN(processor) {}

TEST(processor, init) {
  TEST_ASSERT_EQUAL(*cpu->A, 0);
  TEST_ASSERT_EQUAL(*cpu->B, 0);
  TEST_ASSERT_EQUAL(*cpu->C, 0);
  TEST_ASSERT_EQUAL(*cpu->D, 0);
  TEST_ASSERT_EQUAL(*cpu->E, 0);
  TEST_ASSERT_EQUAL(*cpu->F, 0);
  TEST_ASSERT_EQUAL(*cpu->H, 0);
  TEST_ASSERT_EQUAL(*cpu->L, 0);

  TEST_ASSERT_EQUAL(cpu->PC, 0x0000);
  TEST_ASSERT_EQUAL(cpu->SP, 0xFFFE);
}

TEST(processor, ptrs)
{
    *cpu->AF = 0x55AA;
    TEST_ASSERT_EQUAL(0xAA, *cpu->F);
    TEST_ASSERT_EQUAL(0x55, *cpu->A);

    *cpu->BC = 0x55AA;
    TEST_ASSERT_EQUAL(0xAA, *cpu->C);
    TEST_ASSERT_EQUAL(0x55, *cpu->B);

    *cpu->DE = 0x55AA;
    TEST_ASSERT_EQUAL(0xAA, *cpu->E);
    TEST_ASSERT_EQUAL(0x55, *cpu->D);

    *cpu->HL = 0x55AA;
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


TEST(processor, poppush)
{
    CPU_stack_push(0xCC12);
    TEST_ASSERT_EQUAL(0xFFFC, cpu->SP);
    TEST_ASSERT_EQUAL(0xCC12, CPU_stack_pop());
}

TEST(processor, ints) {
  TEST_ASSERT_EQUAL(0x00, memory->memory[0xFF0F]);
  CPU_set_interrupt(cpu, INT_V_BLANK);
  TEST_ASSERT_EQUAL(0x01, memory->memory[0xFF0F]);
}
