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
  gb_cpu->SP = 0xFFFE;
}

TEST_TEAR_DOWN(processor) {}

TEST(processor, init) {
  TEST_ASSERT_EQUAL(0, *cpu->A);
  TEST_ASSERT_EQUAL(0, *cpu->B);
  TEST_ASSERT_EQUAL(0, *cpu->C);
  TEST_ASSERT_EQUAL(0, *cpu->D);
  TEST_ASSERT_EQUAL(0, *cpu->E);
  TEST_ASSERT_EQUAL(0, *cpu->F);
  TEST_ASSERT_EQUAL(0, *cpu->H);
  TEST_ASSERT_EQUAL(0, *cpu->L);

  TEST_ASSERT_EQUAL(0x0000, cpu->PC);
  TEST_ASSERT_EQUAL(0xFFFE, cpu->SP);
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
    CPU_set_flag(CARRY_FLAG, 1);
    TEST_ASSERT_EQUAL(1, CPU_check_flag(CARRY_FLAG));

    CPU_init(gb_cpu);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));

    CPU_set_flag(CARRY_FLAG, 0);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));

    CPU_set_flag(HALF_CARRY_FLAG, 1);
    TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
    CPU_set_flag(HALF_CARRY_FLAG, 0);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(HALF_CARRY_FLAG));

    CPU_set_flag(ZERO_FLAG, 1);
    TEST_ASSERT_EQUAL(1, CPU_check_flag(ZERO_FLAG));
    CPU_set_flag(ZERO_FLAG, 0);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));

    CPU_set_flag(SUBTRACT_FLAG, 1);
    TEST_ASSERT_EQUAL(1, CPU_check_flag(SUBTRACT_FLAG));
    CPU_set_flag(SUBTRACT_FLAG, 0);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
}


TEST(processor, poppush)
{
    CPU_stack_push(0xCC12);
    TEST_ASSERT_EQUAL(0xFFFC, cpu->SP);
    TEST_ASSERT_EQUAL(0xCC12, CPU_stack_pop());
}

TEST(processor, ints) {

  cpu->ime = 1;
  memory_write8(0xFFFF, 0xFF); //enable all interrupts

  TEST_ASSERT_EQUAL(0x00, memory_read8(memory, 0xFF0F));
  CPU_set_interrupt(cpu, INT_V_BLANK);
  TEST_ASSERT_EQUAL(0x01, memory_read8(memory, 0xFF0F));

  memory_write8(0xFF0F, 0);
  TEST_ASSERT_EQUAL(0x00, memory_read8(memory, 0xFF0F));
  CPU_set_interrupt(cpu, INT_LCD_STAT);
  TEST_ASSERT_EQUAL(0x02, memory_read8(memory, 0xFF0F));

  memory_write8(0xFF0F, 0);
  TEST_ASSERT_EQUAL(0x00, memory_read8(memory, 0xFF0F));
  CPU_set_interrupt(cpu, INT_TMR);
  TEST_ASSERT_EQUAL(0x04, memory_read8(memory, 0xFF0F));

  memory_write8(0xFF0F, 0);
  TEST_ASSERT_EQUAL(0x00, memory_read8(memory, 0xFF0F));
  CPU_set_interrupt(cpu, INT_SERIAL);
  TEST_ASSERT_EQUAL(0x08, memory_read8(memory, 0xFF0F));

  memory_write8(0xFF0F, 0);
  TEST_ASSERT_EQUAL(0x00, memory_read8(memory, 0xFF0F));
  CPU_set_interrupt(cpu, INT_JOYPAD);
  TEST_ASSERT_EQUAL(0x10, memory_read8(memory, 0xFF0F));
}

TEST(processor, handle_int) {
    gb_cpu->PC = 0xAA55;
    gb_cpu->ime = 1;
    CPU_set_interrupt(cpu, INT_V_BLANK);
    CPU_enable_interrupt(cpu, INT_V_BLANK);
    CPU_handle_interrupt(gb_cpu);
    TEST_ASSERT_EQUAL(0x0040, gb_cpu->PC);
    TEST_ASSERT_EQUAL(0xFFFC, gb_cpu->SP);
    TEST_ASSERT_EQUAL(0xAA55, CPU_stack_pop());
}
