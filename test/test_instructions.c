#include "CPU.h"
#include "instructions.h"
#include "memory.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Instructions);

TEST_SETUP(Instructions) {
  CPU_init(gb_cpu);
  memory_init(memory);
}

TEST_TEAR_DOWN(Instructions) {}

CPU_t cpu;

TEST(Instructions, adc) {
  // Register A + #
  uint8_t n = 10;
  uint8_t A = 0;

  // Normal Add
  CPU_set_flag(CARRY_FLAG);
  instr_adc(&A, n);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(CARRY_FLAG));
  TEST_ASSERT_EQUAL(11, A);

  // Z Flag
  A = 0;
  CPU_init(gb_cpu);
  instr_adc(&A, 0);
  TEST_ASSERT_EQUAL(1, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, A);

  // H Flag
  A = 0x0F;
  CPU_init(gb_cpu);
  instr_adc(&A, 1);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));

  // C Flag
  A =0x80 ;
  CPU_init(gb_cpu);
  instr_adc(&A, 0x81);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(CARRY_FLAG));
}

TEST(Instructions, add8) {
    uint8_t A,n;

    CPU_init(gb_cpu);
    n = 0x01;
    A = 0x0F;
    instr_add(&A, n);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
    TEST_ASSERT_EQUAL(0x10, A);

    CPU_init(gb_cpu);
    n = 0x80;
    A = 0;
    CPU_set_flag(SUBTRACT_FLAG);
    instr_add(&A, n);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
    TEST_ASSERT_EQUAL(0x80, A);

    CPU_init(gb_cpu);
    n = 0xFF;
    A = 0x02;
    instr_add(&A, n);
    TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
    // TEST_ASSERT_EQUAL(1, CPU_check_flag(CARRY_FLAG));
    TEST_ASSERT_EQUAL(1, A);

    CPU_init(gb_cpu);
    n = 0x00;
    A = 0x00;
    instr_add(&A, n);
    TEST_ASSERT_EQUAL(1, CPU_check_flag(ZERO_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
    // TEST_ASSERT_EQUAL(0, CPU_check_flag(HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
    TEST_ASSERT_EQUAL(0, A);
}

TEST(Instructions, add_SP) {

  uint8_t n = 0xAA;

  // addition
  CPU_init(gb_cpu);
  cpu.SP = 0x00;
  instr_add_SP(&cpu.SP, n);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
  TEST_ASSERT_EQUAL(0xAA, cpu.SP);

  CPU_init(gb_cpu);
  cpu.SP = 0xFFFF;
  n = 0x01;
  instr_add_SP(&cpu.SP, n);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(CARRY_FLAG));
  TEST_ASSERT_EQUAL(0x00, cpu.SP);
}

TEST(Instructions, add_HL) {
  uint16_t n = 0x55AA;

  // addition
  CPU_init(gb_cpu);
  CPU_set_flag(SUBTRACT_FLAG);
  instr_add_HL(&cpu.HL, n);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
  TEST_ASSERT_EQUAL(0x55AA, cpu.HL);

  // Carry + HC + Zero
  n = 0x0001;
  CPU_init(gb_cpu);
  CPU_set_flag(SUBTRACT_FLAG);
  cpu.HL = 0xFFFF;
  instr_add_HL(&cpu.HL, n);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(CARRY_FLAG));
  TEST_ASSERT_EQUAL(0x0000, cpu.HL);

  // HC
  n = 0x0800;
  CPU_init(gb_cpu);
  CPU_set_flag(SUBTRACT_FLAG);
  cpu.HL = 0x0800;
  instr_add_HL(&cpu.HL, n);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
  TEST_ASSERT_EQUAL(0x1000, cpu.HL);
}

TEST(Instructions, and) {

  CPU_init(gb_cpu);
  cpu.A = 0x55;
  instr_and(&cpu.A, 0x55);
  TEST_ASSERT_EQUAL(0x55, cpu.A);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));

  CPU_init(gb_cpu);
  cpu.A = 0xAA;
  instr_and(&cpu.A, 0x55);
  TEST_ASSERT_EQUAL(0x00, cpu.A);
  TEST_ASSERT_EQUAL(1, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
}

TEST(Instructions, bit) {

  CPU_init(gb_cpu);
  uint8_t r = 0x10;
  uint8_t b = 4;
  instr_bit(&b, &r);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));

  CPU_init(gb_cpu);
  r = 0x20;
  b = 4;
  instr_bit(&b, &r);
  TEST_ASSERT_EQUAL(1, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
}

TEST(Instructions, call_n) {

  memory_init(memory);
  CPU_init(gb_cpu);
  gb_cpu->PC = 0;
  instr_call_n(0xAA55);
  TEST_ASSERT_EQUAL(0xAA55 , gb_cpu->PC);
  TEST_ASSERT_EQUAL(0xFFFC, gb_cpu->SP);
  TEST_ASSERT_EQUAL(0x0001, CPU_stack_pop());
}

TEST(Instructions, ccf) {

  CPU_init(gb_cpu);
  CPU_set_flag(CARRY_FLAG);
  instr_ccf();
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));

  CPU_init(gb_cpu);
  CPU_clear_flag(CARRY_FLAG);
  instr_ccf();
  TEST_ASSERT_EQUAL(1, CPU_check_flag(CARRY_FLAG));
}

TEST(Instructions, cpl) {

  CPU_init(gb_cpu);
  *gb_cpu->A = 0x55;
  instr_cpl(gb_cpu->A);
  TEST_ASSERT_EQUAL(1, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0xAA, *gb_cpu->A);
}

TEST(Instructions, inc) {
    *gb_cpu->A = 0x00;
    instr_inc_n(gb_cpu->A);
    TEST_ASSERT_EQUAL(0x01, *gb_cpu->A);
}

TEST(Instructions, inc_nn) {
    instr_inc_nn(&gb_cpu->BC);
    TEST_ASSERT_EQUAL(0x0001, gb_cpu->BC);
}

TEST(Instructions, jp) {
  cpu.PC = 0;
  instr_jp(gb_cpu, 0xAA55);
  TEST_ASSERT_EQUAL(0xAA55, cpu.PC);
}

TEST(Instructions, jp_hl) {
  memory->memory[0xAA55] = 0xBB;
  cpu.registers.H = 0xAA;
  cpu.registers.L = 0x55;
  cpu.PC = 0;
  instr_jp_hl(gb_cpu);
  TEST_ASSERT_EQUAL(0xBB00, cpu.PC);
}

TEST(Instructions, jr) {
  cpu.PC = 0;
  instr_jr(gb_cpu, 0x55);
  TEST_ASSERT_EQUAL(0x55, cpu.PC);
}

TEST(Instructions, load_an) {
  instr_load_an(gb_cpu, 0x55);
  TEST_ASSERT_EQUAL(0x55, cpu.registers.A);
}

TEST(Instructions, load_na) {
  cpu.registers.A = 0x55;
  instr_load_na(gb_cpu, gb_cpu->registers.B);
  TEST_ASSERT_EQUAL(0x55, cpu.registers.B);
}

TEST(Instructions, srl) {
  cpu.registers.A = 0x01;
  instr_srl(gb_cpu, cpu.registers.A);
  TEST_ASSERT_EQUAL(1, CPU_check_flag(CARRY_FLAG));

  cpu.registers.A = 0x00;
  instr_srl(gb_cpu, cpu.registers.A);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
}

TEST(Instructions, xor) {
  cpu.registers.A = 0x55;
  instr_xor(gb_cpu, 0x55);
  TEST_ASSERT_EQUAL(0x00, cpu.registers.A);
}
