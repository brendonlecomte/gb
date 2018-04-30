#include "CPU.h"
#include "instructions.h"
#include "memory.h"
#include "unity.h"
#include "unity_fixture.h"
#include "op_codes.h"


TEST_GROUP(Instructions);

TEST_SETUP(Instructions) {
  CPU_init(gb_cpu);
  memory_init(memory);
}

TEST_TEAR_DOWN(Instructions) {}

TEST(Instructions, adc) {
  // Register A + #
  uint8_t n = 0x0A;
  uint8_t A = 0;

  // Normal Add
  CPU_set_flag(CARRY_FLAG, 1);
  instr_adc(&A, n);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
  TEST_ASSERT_EQUAL(0x0B, A);

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

  // C Flag
  A = 0xFF;
  CPU_init(gb_cpu);
  CPU_set_flag(CARRY_FLAG, 0);
  instr_adc(&A, 0x01);
  TEST_ASSERT_EQUAL(0, A);
  TEST_ASSERT_EQUAL(1, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
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
    CPU_set_flag(SUBTRACT_FLAG, 1);
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

    CPU_init(gb_cpu);
    n = 0x08;
    A = 0xF8;
    instr_add(&A, n);
    TEST_ASSERT_EQUAL(0, A);
    TEST_ASSERT_EQUAL(1, CPU_check_flag(ZERO_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(1, CPU_check_flag(CARRY_FLAG));
}

TEST(Instructions, add_SP) {

  uint8_t n = 0xAA;

  // addition
  CPU_init(gb_cpu);
  gb_cpu->SP = 0x00;
  instr_add_SP(&gb_cpu->SP, n);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
  TEST_ASSERT_EQUAL(0xAA, gb_cpu->SP);

  CPU_init(gb_cpu);
  gb_cpu->SP = 0xFFFF;
  n = 0x01;
  instr_add_SP(&gb_cpu->SP, n);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(CARRY_FLAG));
  TEST_ASSERT_EQUAL(0x00, gb_cpu->SP);
}

TEST(Instructions, add_HL) {
  uint16_t n;

  // addition
  n = 0x55AA;
  CPU_set_flag(SUBTRACT_FLAG, 1);
  *gb_cpu->HL = 0x00;
  instr_add_HL(gb_cpu->HL, n);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
  TEST_ASSERT_EQUAL(0x55AA, *gb_cpu->HL);

  // Carry + HC + Zero
  n = 0x0001;
  CPU_init(gb_cpu);
  CPU_set_flag(SUBTRACT_FLAG, 1);
  *gb_cpu->HL = 0xFFFF;
  instr_add_HL(gb_cpu->HL, n);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(CARRY_FLAG));
  TEST_ASSERT_EQUAL(0x0000, *gb_cpu->HL);

  // HC
  n = 0x0800;
  CPU_init(gb_cpu);
  CPU_set_flag(SUBTRACT_FLAG, 1);
  *gb_cpu->HL = 0x0800;
  instr_add_HL(gb_cpu->HL, n);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
  TEST_ASSERT_EQUAL(0x1000, *gb_cpu->HL);
}

TEST(Instructions, and) {
  CPU_init(gb_cpu);
  *gb_cpu->A = 0x55;
  instr_and(gb_cpu->A, 0x55);
  TEST_ASSERT_EQUAL(0x55, *gb_cpu->A);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));

  CPU_init(gb_cpu);
  *gb_cpu->A = 0xAA;
  instr_and(gb_cpu->A, 0x55);
  TEST_ASSERT_EQUAL(0x00, *gb_cpu->A);
  TEST_ASSERT_EQUAL(1, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
}

TEST(Instructions, bit) {

  CPU_init(gb_cpu);
  uint8_t r = 0x10;
  uint8_t b = 4;
  instr_bit(b, &r);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));

  CPU_init(gb_cpu);
  r = 0x20;
  b = 4;
  instr_bit(b, &r);
  TEST_ASSERT_EQUAL(1, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));

  CPU_init(gb_cpu);
  r = 0x81;
  b = 7;
  instr_bit(b, &r);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(SUBTRACT_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
}

TEST(Instructions, call_n) {
  memory_init(memory);
  CPU_init(gb_cpu);

  gb_cpu->PC = 0x0001;
  instr_call_n(0xAA55);
  TEST_ASSERT_EQUAL(0xAA55 , gb_cpu->PC);
  TEST_ASSERT_EQUAL(0xFFFC, gb_cpu->SP);
  TEST_ASSERT_EQUAL(0x0001, CPU_stack_pop());

  //bgb test
  *gb_cpu->AF = 0x7780;
  *gb_cpu->BC = 0x0000;
  *gb_cpu->DE = 0xFF56;
  *gb_cpu->HL = 0x0B8F;
  gb_cpu->SP = 0xDFFF;
  gb_cpu->PC = 0x0453;
  instr_call_n(0x02A3);
  TEST_ASSERT_EQUAL(0x7780, *gb_cpu->AF);
  TEST_ASSERT_EQUAL(0x0000, *gb_cpu->BC);
  TEST_ASSERT_EQUAL(0xFF56, *gb_cpu->DE);
  TEST_ASSERT_EQUAL(0x0B8F, *gb_cpu->HL);
  TEST_ASSERT_EQUAL(0xDFFD, gb_cpu->SP);
  TEST_ASSERT_EQUAL(0x02A3, gb_cpu->PC);
}

TEST(Instructions, ccf) {

  CPU_init(gb_cpu);
  CPU_set_flag(CARRY_FLAG, 1);
  instr_ccf();
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));

  CPU_init(gb_cpu);
  CPU_set_flag(CARRY_FLAG, 0);
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

TEST(Instructions, daa) {
  TEST_ASSERT_EQUAL(0,1);
}

TEST(Instructions, cp) {
  uint8_t x = 0xAA;
  instr_cp(&x, 0xAA);
  TEST_ASSERT_EQUAL(1, CPU_check_flag(SUBTRACT_FLAG));
  // TEST_ASSERT_EQUAL(0, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));

  x = 0xAA;
  instr_cp(&x, 0x55);
  TEST_ASSERT_EQUAL(1, CPU_check_flag(SUBTRACT_FLAG));
  // TEST_ASSERT_EQUAL(0, CPU_check_flag(HALF_CARRY_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));

  *gb_cpu->AF = 0x9200;
  *gb_cpu->BC = 0xFB1F;
  *gb_cpu->DE = 0xFF56;
  *gb_cpu->HL = 0x0B8F;
  gb_cpu->SP = 0xDFF3;
  gb_cpu->PC = 0x0745;

  instr_cp(gb_cpu->A, 0x90);
  TEST_ASSERT_EQUAL(0x9240, *gb_cpu->AF);
  TEST_ASSERT_EQUAL(0xFB1F, *gb_cpu->BC);
  TEST_ASSERT_EQUAL(0xFF56, *gb_cpu->DE);
  TEST_ASSERT_EQUAL(0x0B8F, *gb_cpu->HL);
  TEST_ASSERT_EQUAL(0xDFF3, gb_cpu->SP);
  TEST_ASSERT_EQUAL(0x0745, gb_cpu->PC);
}

TEST(Instructions, dec_n) {
    uint8_t x = 0xAA;
    instr_dec_n(&x);
    TEST_ASSERT_EQUAL(1, CPU_check_flag(SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
    TEST_ASSERT_EQUAL(0xA9, x);

    x = 0xA0;
    instr_dec_n(&x);
    TEST_ASSERT_EQUAL(1, CPU_check_flag(SUBTRACT_FLAG));
    TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
    TEST_ASSERT_EQUAL(0, CPU_check_flag(ZERO_FLAG));
    TEST_ASSERT_EQUAL(0x9F, x);
}

TEST(Instructions, dec_nn) {
  *gb_cpu->BC = 0x0055;
  instr_dec_nn(gb_cpu->BC);
  TEST_ASSERT_EQUAL(0x0054, *gb_cpu->BC);
}

TEST(Instructions, di) {
  instr_di();
  TEST_ASSERT_EQUAL(0, gb_cpu->ime);
}

TEST(Instructions, ei) {
  instr_ei();
  TEST_ASSERT_EQUAL(1, gb_cpu->ime);
}

TEST(Instructions, inc) {
    *gb_cpu->A = 0x00;
    instr_inc_n(gb_cpu->A);
    TEST_ASSERT_EQUAL(0x01, *gb_cpu->A);
}

TEST(Instructions, inc_nn) {
    instr_inc_nn(gb_cpu->BC);
    TEST_ASSERT_EQUAL(0x0001, *gb_cpu->BC);

    //bgb test
    *gb_cpu->AF = 0xC380;
    *gb_cpu->BC = 0x0000;
    *gb_cpu->DE = 0xFF56;
    *gb_cpu->HL = 0x0392;
    gb_cpu->SP = 0xDFF7;
    instr_inc_nn(gb_cpu->HL);
    TEST_ASSERT_EQUAL(0xC380, *gb_cpu->AF);
    TEST_ASSERT_EQUAL(0x0000, *gb_cpu->BC);
    TEST_ASSERT_EQUAL(0xFF56, *gb_cpu->DE);
    TEST_ASSERT_EQUAL(0x0393, *gb_cpu->HL);
    TEST_ASSERT_EQUAL(0xDFF7, gb_cpu->SP);
}

TEST(Instructions, jp) {
  gb_cpu->PC = 0;
  instr_jp(0xAA55);
  TEST_ASSERT_EQUAL(0xAA55, gb_cpu->PC);

  //bgb test
  *gb_cpu->AF = 0x1180;
  *gb_cpu->BC = 0x0000;
  *gb_cpu->DE = 0xFF56;
  *gb_cpu->HL = 0x000D;
  gb_cpu->SP = 0xFFFE;
  gb_cpu->PC = 0x0637;
  instr_jp(0x0430);
  TEST_ASSERT_EQUAL(0x1180, *gb_cpu->AF);
  TEST_ASSERT_EQUAL(0x0000, *gb_cpu->BC);
  TEST_ASSERT_EQUAL(0xFF56, *gb_cpu->DE);
  TEST_ASSERT_EQUAL(0x000D, *gb_cpu->HL);
  TEST_ASSERT_EQUAL(0xFFFE, gb_cpu->SP);
  TEST_ASSERT_EQUAL(0x0430, gb_cpu->PC);
}

TEST(Instructions, jp_hl) {
  memory->memory[0xAA55] = 0xBB;
  *gb_cpu->HL = 0xAA55;
  gb_cpu->PC = 0;
  instr_jp_hl();
  TEST_ASSERT_EQUAL(0x00BB, gb_cpu->PC);
}

TEST(Instructions, jr) {
  gb_cpu->PC = 0;
  instr_jr(0x55);
  TEST_ASSERT_EQUAL(0x0056, gb_cpu->PC);

  gb_cpu->PC = 0x000B;
  instr_jr(0xFB);
  TEST_ASSERT_EQUAL(0x0007, gb_cpu->PC);

  gb_cpu->PC = 0x0217;
  instr_jr(0xFC);
  TEST_ASSERT_EQUAL(0x0214, gb_cpu->PC);

  *gb_cpu->AF = 0xC380;
  *gb_cpu->BC = 0x0000;
  *gb_cpu->DE = 0xFF56;
  *gb_cpu->HL = 0x0395;
  gb_cpu->SP = 0xDFFF;
  gb_cpu->PC = 0x0393;
  // gb_cpu->PC += 1;
  instr_jr(0x02);
  TEST_ASSERT_EQUAL(0xC380, *gb_cpu->AF);
  TEST_ASSERT_EQUAL(0x0000, *gb_cpu->BC);
  TEST_ASSERT_EQUAL(0xFF56, *gb_cpu->DE);
  TEST_ASSERT_EQUAL(0x0395, *gb_cpu->HL);
  TEST_ASSERT_EQUAL(0xDFFF, gb_cpu->SP);
  TEST_ASSERT_EQUAL(0x0396, gb_cpu->PC);
}

TEST(Instructions, load_ab) {
  *gb_cpu->A = 0x55;
  *gb_cpu->B = 0xAA;
  instr_load_ab(gb_cpu->A, *gb_cpu->B);
  TEST_ASSERT_EQUAL(0xAA, *gb_cpu->B);

  *gb_cpu->C = 0x55;
  instr_load_ab(gb_cpu->C, 0x11);
  TEST_ASSERT_EQUAL(0x11, *gb_cpu->C);

  //bgb test
  *gb_cpu->AF = 0x1180;
  *gb_cpu->BC = 0x0000;
  *gb_cpu->DE = 0xFF56;
  *gb_cpu->HL = 0x000D;
  gb_cpu->SP = 0xDFFF;
  gb_cpu->PC = 0x0437;
  instr_load_ab(gb_cpu->A, 0x00);
  TEST_ASSERT_EQUAL(0x0080, *gb_cpu->AF);
  TEST_ASSERT_EQUAL(0x0000, *gb_cpu->BC);
  TEST_ASSERT_EQUAL(0xFF56, *gb_cpu->DE);
  TEST_ASSERT_EQUAL(0x000D, *gb_cpu->HL);
  TEST_ASSERT_EQUAL(0xDFFF, gb_cpu->SP);
  TEST_ASSERT_EQUAL(0x0437, gb_cpu->PC);
}

TEST(Instructions, load_ab16) {
  *gb_cpu->BC = 0x55CC;
  *gb_cpu->DE = 0xAABB;
  instr_load_ab16(gb_cpu->BC, *gb_cpu->DE);
  TEST_ASSERT_EQUAL(0xAABB, *gb_cpu->BC);

  //bgb test
  *gb_cpu->AF = 0x1180;
  *gb_cpu->BC = 0x0000;
  *gb_cpu->DE = 0xFF56;
  *gb_cpu->HL = 0x000D;
  gb_cpu->SP = 0xFFFE;
  gb_cpu->PC = 0x0637;
  instr_load_ab16(&gb_cpu->SP, 0xDFFF);
  TEST_ASSERT_EQUAL(0x1180, *gb_cpu->AF);
  TEST_ASSERT_EQUAL(0x0000, *gb_cpu->BC);
  TEST_ASSERT_EQUAL(0xFF56, *gb_cpu->DE);
  TEST_ASSERT_EQUAL(0x000D, *gb_cpu->HL);
  TEST_ASSERT_EQUAL(0xDFFF, gb_cpu->SP);
  TEST_ASSERT_EQUAL(0x0637, gb_cpu->PC);

  //bgb test
  *gb_cpu->AF = 0x7780;
  *gb_cpu->BC = 0x0000;
  *gb_cpu->DE = 0xFF56;
  *gb_cpu->HL = 0x000D;
  gb_cpu->SP = 0xDFFF;
  gb_cpu->PC = 0x0453;
  instr_load_ab16(gb_cpu->HL, 0x0B8F);
  TEST_ASSERT_EQUAL(0x7780, *gb_cpu->AF);
  TEST_ASSERT_EQUAL(0x0000, *gb_cpu->BC);
  TEST_ASSERT_EQUAL(0xFF56, *gb_cpu->DE);
  TEST_ASSERT_EQUAL(0x0B8F, *gb_cpu->HL);
  TEST_ASSERT_EQUAL(0xDFFF, gb_cpu->SP);
  TEST_ASSERT_EQUAL(0x0453, gb_cpu->PC);
}

TEST(Instructions, srl) {
  *gb_cpu->A = 0x01;
  instr_srl(gb_cpu->A);
  TEST_ASSERT_EQUAL(1, CPU_check_flag(CARRY_FLAG));

  *gb_cpu->A = 0x00;
  instr_srl(gb_cpu->A);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
}

TEST(Instructions, or){
  *gb_cpu->A = 0x55;
  instr_or(gb_cpu->A, 0xAA);
  TEST_ASSERT_EQUAL(0xFF, *gb_cpu->A);

  *gb_cpu->AF = 0xFB80;
  *gb_cpu->BC = 0xFB1F;
  *gb_cpu->DE = 0xFF56;
  *gb_cpu->HL = 0x0B8F;
  gb_cpu->SP = 0xDFF3;
  gb_cpu->PC = 0x0393;
  // gb_cpu->PC += 1;
  instr_or(gb_cpu->A, *gb_cpu->C);
  TEST_ASSERT_EQUAL(0xFF00, *gb_cpu->AF);
  TEST_ASSERT_EQUAL(0xFB1F, *gb_cpu->BC);
  TEST_ASSERT_EQUAL(0xFF56, *gb_cpu->DE);
  TEST_ASSERT_EQUAL(0x0B8F, *gb_cpu->HL);
  TEST_ASSERT_EQUAL(0xDFF3, gb_cpu->SP);
  TEST_ASSERT_EQUAL(0x0393, gb_cpu->PC);

  // AF:0xFB50 BC:0xFBAE DE:0xD000 HL:0xCB8F SP:0xDFF3 IME:0x0 IF:0x00 IE:0x00
  // PC:0xC736 OP:0xB1 AF:0xFF00 BC:0xFBAE DE:0xD000 HL:0xCB8F SP:0xDFF3 IME:0x0 IF:0x00 IE:0x00
  *gb_cpu->AF = 0xFB50;
  *gb_cpu->BC = 0xFBAE;
  *gb_cpu->DE = 0xD000;
  *gb_cpu->HL = 0xCB8F;
  gb_cpu->SP = 0xDFF3;
    // gb_cpu->PC += 1;
  instr_or(gb_cpu->A, *gb_cpu->C);
  TEST_ASSERT_EQUAL(0xFF00, *gb_cpu->AF);
  TEST_ASSERT_EQUAL(0xFBAE, *gb_cpu->BC);
  TEST_ASSERT_EQUAL(0xD000, *gb_cpu->DE);
  TEST_ASSERT_EQUAL(0xCB8F, *gb_cpu->HL);

}

TEST(Instructions, push) {
  uint16_t x = 0x1234;
  instr_push(x);
  TEST_ASSERT_EQUAL(0xFFFC, gb_cpu->SP);
  TEST_ASSERT_EQUAL(0x1234, CPU_stack_pop());
}

TEST(Instructions, pop) {
  uint16_t x;
  CPU_stack_push(0xABCD);
  instr_pop(&x);
  TEST_ASSERT_EQUAL(0xABCD, x);
}

TEST(Instructions, res) {
  uint8_t x = 0xFF;
  instr_res(4, &x);
  TEST_ASSERT_EQUAL(0xEF, x);
}

TEST(Instructions, ret) {
  CPU_stack_push(0x1234);
  instr_ret();
  TEST_ASSERT_EQUAL(0x1234, gb_cpu->PC);
}

TEST(Instructions, rl) {
  uint8_t x = 0xAA;
  CPU_set_flag(CARRY_FLAG, 1);
  instr_rl(&x);
  TEST_ASSERT_EQUAL(0x55, x);
  TEST_ASSERT_EQUAL(1, CPU_check_flag(CARRY_FLAG));


  x = 0x55;
  CPU_set_flag(CARRY_FLAG, 0);
  instr_rl(&x);
  TEST_ASSERT_EQUAL(0xAA, x);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
}

TEST(Instructions, rlc) {
  uint8_t x = 0xCC;
  CPU_set_flag(CARRY_FLAG, 0);
  instr_rlc(&x);
  TEST_ASSERT_EQUAL(0x99, x);
  TEST_ASSERT_EQUAL(1, CPU_check_flag(CARRY_FLAG));


  x = 0x66;
  CPU_set_flag(CARRY_FLAG, 1);
  instr_rlc(&x);
  TEST_ASSERT_EQUAL(0xcc, x);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
}

TEST(Instructions, rr) {
  uint8_t x = 0x76;
  CPU_set_flag(CARRY_FLAG, 0);
  instr_rr(&x);
  TEST_ASSERT_EQUAL(0x3B, x);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));


  x = 0x75;
  CPU_set_flag(CARRY_FLAG, 1);
  instr_rr(&x);
  TEST_ASSERT_EQUAL(0xBA, x);
  TEST_ASSERT_EQUAL(1, CPU_check_flag(CARRY_FLAG));

  x = 0x00;
  CPU_set_flag(CARRY_FLAG, 0);
  instr_rr(&x);
  TEST_ASSERT_EQUAL(0x00, x);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));
  TEST_ASSERT_EQUAL(1, CPU_check_flag(ZERO_FLAG));
}

TEST(Instructions, rrc) {
  uint8_t x = 0xB8;
  CPU_set_flag(CARRY_FLAG, 1);
  instr_rrc(&x);
  TEST_ASSERT_EQUAL(0x5c, x);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(CARRY_FLAG));


  x = 0x4D;
  CPU_set_flag(CARRY_FLAG, 0);
  instr_rrc(&x);
  TEST_ASSERT_EQUAL(0xA6, x);
  TEST_ASSERT_EQUAL(1, CPU_check_flag(CARRY_FLAG));
}

TEST(Instructions, rst) {
  gb_cpu->PC = 0x1234;
  instr_rst(0x08);
  TEST_ASSERT_EQUAL(0x0008, gb_cpu->PC);
  TEST_ASSERT_EQUAL(0x1234, CPU_stack_pop());
}

TEST(Instructions, sbc) {
  *gb_cpu->A = 0x50;
  CPU_set_flag(CARRY_FLAG, 1);
  instr_sbc(gb_cpu->A, 0x10);
  TEST_ASSERT_EQUAL(0x3F, *gb_cpu->A);
  TEST_ASSERT_EQUAL(0, CPU_check_flag(HALF_CARRY_FLAG));

  // *gb_cpu->A = 0x08;
  // instr_sbc(gb_cpu->A, add);
  // TEST_ASSERT_EQUAL(gb_cpu->A);
  // TEST_ASSERT_EQUAL(1, CPU_check_flag(HALF_CARRY_FLAG));
}

TEST(Instructions, sub) {
  *gb_cpu->A = 0x50;
  CPU_set_flag(CARRY_FLAG, 1);
  instr_sub_n(gb_cpu->A, 0x10);
  TEST_ASSERT_EQUAL(0x40, *gb_cpu->A);
  // TEST_ASSERT_EQUAL(2, CPU_check_flag(HALF_CARRY_FLAG));

  //bgb test
  *gb_cpu->AF = 0xDF60;
  *gb_cpu->BC = 0x00FF;
  *gb_cpu->DE = 0x0B79;
  *gb_cpu->HL = 0x0B81;
  gb_cpu->SP = 0xDFE7;
  gb_cpu->PC = 0x0213;
  instr_sub_n(gb_cpu->A, 0x05);
  TEST_ASSERT_EQUAL(0xDA40, *gb_cpu->AF);
  TEST_ASSERT_EQUAL(0x00FF, *gb_cpu->BC);
  TEST_ASSERT_EQUAL(0x0B79, *gb_cpu->DE);
  TEST_ASSERT_EQUAL(0x0B81, *gb_cpu->HL);
  TEST_ASSERT_EQUAL(0xDFE7, gb_cpu->SP);
  // TEST_ASSERT_EQUAL(0x0215, gb_cpu->PC);
}

TEST(Instructions, swap) {
  uint8_t x = 0xA5;
  instr_swap(&x);
  TEST_ASSERT_EQUAL(0x5A, x);
}

TEST(Instructions, xor) {
  *gb_cpu->A = 0x55;
  instr_xor(gb_cpu->A, 0x55);
  TEST_ASSERT_EQUAL(0x00, *gb_cpu->A);
}
