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

  // Normal Add
  CPU_init(&cpu);
  CPU_set_flag(&cpu, CARRY_FLAG);
  instr_adc(&cpu, n);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu,HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu,CARRY_FLAG));
  TEST_ASSERT_EQUAL(11 , cpu.registers.A);

  //Z Flag
  CPU_init(&cpu);
  instr_adc(&cpu, 0);
  TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, CARRY_FLAG));
  TEST_ASSERT_EQUAL(0 , cpu.registers.A);

  //H Flag
  CPU_init(&cpu);
  cpu.registers.A = 0x0F;
  instr_adc(&cpu, 1);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, CARRY_FLAG));

  //C Flag
  CPU_init(&cpu);
  cpu.registers.A = 0x80;
  instr_adc(&cpu, 0x81);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, CARRY_FLAG));
}

TEST(Instructions, add_A)
{
    CPU_t cpu;
    uint8_t n = 0x80;
    CPU_init(&cpu);
    CPU_set_flag(&cpu, SUBTRACT_FLAG);
    instr_add_A(&cpu, n);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, ZERO_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, CARRY_FLAG));
    TEST_ASSERT_EQUAL(0x80 , cpu.registers.A);

    n = 0x01;
    CPU_init(&cpu);
    cpu.registers.A = 0x0F;
    instr_add_A(&cpu, n);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, ZERO_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, CARRY_FLAG));
    TEST_ASSERT_EQUAL(0x10 , cpu.registers.A);

    n = 0xFF;
    CPU_init(&cpu);
    cpu.registers.A = 0x02;
    instr_add_A(&cpu, n);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, ZERO_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, CARRY_FLAG));
    TEST_ASSERT_EQUAL(1, cpu.registers.A);

    n = 0x00;
    CPU_init(&cpu);
    instr_add_A(&cpu, n);
    TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, ZERO_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, CARRY_FLAG));
    TEST_ASSERT_EQUAL(0 , cpu.registers.A);


}

TEST(Instructions, add_SP)
{
    CPU_t cpu;
    uint8_t n = 0xAA;

    //addition
    CPU_init(&cpu);
    cpu.SP = 0x00;
    instr_add_SP(&cpu, n);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, ZERO_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, CARRY_FLAG));
    TEST_ASSERT_EQUAL(0xAA , cpu.SP);

    CPU_init(&cpu);
    cpu.SP = 0xFFFF;
    n = 0x01;
    instr_add_SP(&cpu, n);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, ZERO_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, CARRY_FLAG));
    TEST_ASSERT_EQUAL(0x00, cpu.SP);
}

TEST(Instructions, add_HL)
{
    CPU_t cpu;
    uint16_t n = 0x55AA;

    //addition
    CPU_init(&cpu);
    CPU_set_flag(&cpu, SUBTRACT_FLAG);
    instr_add_HL(&cpu, n);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, ZERO_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, CARRY_FLAG));
    TEST_ASSERT_EQUAL(0x55 , cpu.registers.H);
    TEST_ASSERT_EQUAL(0xAA , cpu.registers.L);

    //Carry + Zero
    n = 0x8000;
    CPU_init(&cpu);
    CPU_set_flag(&cpu, SUBTRACT_FLAG);
    cpu.registers.H = 0x80;
    cpu.registers.L = 0x00;
    instr_add_HL(&cpu, n);
    TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, ZERO_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, CARRY_FLAG));
    TEST_ASSERT_EQUAL(0x00 , cpu.registers.H);
    TEST_ASSERT_EQUAL(0x00 , cpu.registers.L);

    //HC
    n = 0x0800;
    CPU_init(&cpu);
    CPU_set_flag(&cpu, SUBTRACT_FLAG);
    cpu.registers.H = 0x08;
    cpu.registers.L = 0x00;
    instr_add_HL(&cpu, n);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, ZERO_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, CARRY_FLAG));
    TEST_ASSERT_EQUAL(0x10 , cpu.registers.H);
    TEST_ASSERT_EQUAL(0x00 , cpu.registers.L);
}

TEST(Instructions, and)
{
    CPU_t cpu;
    CPU_init(&cpu);
    cpu.registers.A = 0x55;
    instr_and(&cpu, 0x55);
    TEST_ASSERT_EQUAL(cpu.registers.A, 0x55);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, ZERO_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, CARRY_FLAG));

    CPU_init(&cpu);
    cpu.registers.A = 0xAA;
    instr_and(&cpu, 0x55);
    TEST_ASSERT_EQUAL(cpu.registers.A, 0x00);
    TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, ZERO_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, CARRY_FLAG));
}

TEST(Instructions, bit)
{
    CPU_t cpu;
    CPU_init(&cpu);
    uint8_t r = 0x10;
    uint8_t b = 4;
    instr_bit(&cpu, b,r);
    TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, ZERO_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, CARRY_FLAG));

    CPU_init(&cpu);
    r = 0x20;
    b = 4;
    instr_bit(&cpu, b,r);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, ZERO_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, CARRY_FLAG));
}

TEST(Instructions, ccf)
{
    CPU_t cpu;
    CPU_init(&cpu);
    CPU_set_flag(&cpu, CARRY_FLAG);
    instr_ccf(&cpu);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(&cpu, CARRY_FLAG));

    CPU_init(&cpu);
    CPU_clear_flag(&cpu, CARRY_FLAG);
    instr_ccf(&cpu);
    TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, CARRY_FLAG));
}

TEST(Instructions, cpl)
{
    CPU_t cpu;
    CPU_init(&cpu);
    *cpu.A = 0x55;
    instr_cpl(&cpu);
    TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(1, CPU_check_flag(&cpu, HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(0xAA, *cpu.A);
}
