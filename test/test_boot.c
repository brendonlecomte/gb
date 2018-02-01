#include "CPU.h"
#include "instructions.h"
#include "memory.h"
#include "op_codes.h"
#include "unity.h"
#include "unity_fixture.h"
#include <string.h>


TEST_GROUP(Boot);

TEST_SETUP(Boot) {
  CPU_init(gb_cpu);
  memory_init(memory);
}

TEST_TEAR_DOWN(Boot) {}

TEST(Boot, zero_vram) {
    memset(&memory->memory[0x8000], 0xFF, 0x2000); //set memory to known state
    TEST_ASSERT_EQUAL(0xFF, memory->memory[0x9000]); //test new state
    for(;;){
        //fetch
        uint8_t op = memory_read8(memory, gb_cpu->PC);  //read OP code
        gb_cpu->PC += 1; //inc pc

        //execute
        op_codes[op]();
        if(gb_cpu->PC == 0x001d) //Run untill fter the first sub
        {
            break;
        }
    }
    for(uint16_t i = 0x9FFF; i >= 0x8000; i--)
    {
     TEST_ASSERT_EQUAL(0, memory->memory[0x9FFF]); //check we cleared it which
    }
}


TEST(Boot, audio) {
    gb_cpu->PC = 0x000C;
    for(;;){
        //fetch
        uint8_t op = memory_read8(memory, gb_cpu->PC);  //read OP code
        gb_cpu->PC += 1; //inc pc

        //execute
        op_codes[op]();
        if(gb_cpu->PC == 0x0027) //Run untill fter the first sub
        {
            break;
        }
    }
    TEST_ASSERT_EQUAL(0x80, memory->memory[0xff26]); //check we cleared it which
    TEST_ASSERT_EQUAL(0xf3, memory->memory[0xff25]); //check we cleared it which
    TEST_ASSERT_EQUAL(0x80, memory->memory[0xff11]); //check we cleared it which
    TEST_ASSERT_EQUAL(0xf3, memory->memory[0xff12]); //check we cleared it which
    TEST_ASSERT_EQUAL(0x77, memory->memory[0xff24]); //check we cleared it which
}
