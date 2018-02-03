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


// AF=$01B0
// BC=$0013
// DE=$00D8
// HL=$014D
// Stack Pointer=$FFFE
// [$FF05] = $00   ; TIMA
// [$FF06] = $00   ; TMA
// [$FF07] = $00   ; TAC
// [$FF10] = $80   ; NR10
// [$FF11] = $BF   ; NR11
// [$FF12] = $F3   ; NR12
// [$FF14] = $BF   ; NR14
// [$FF16] = $3F   ; NR21
// [$FF17] = $00   ; NR22
// [$FF19] = $BF   ; NR24
// [$FF1A] = $7F   ; NR30
// [$FF1B] = $FF   ; NR31
// [$FF1C] = $9F   ; NR32
// [$FF1E] = $BF   ; NR33
// [$FF20] = $FF   ; NR41
// [$FF21] = $00   ; NR42
// [$FF22] = $00   ; NR43
// [$FF23] = $BF   ; NR30
// [$FF24] = $77   ; NR50
// [$FF25] = $F3   ; NR51
// [$FF26] = $F1-GB, $F0-SGB ; NR52
// [$FF40] = $91   ; LCDC
// [$FF42] = $00   ; SCY
// [$FF43] = $00   ; SCX
// [$FF45] = $00   ; LYC
// [$FF47] = $FC   ; BGP
// [$FF48] = $FF   ; OBP0
// [$FF49] = $FF   ; OBP1
// [$FF4A] = $00   ; WY
// [$FF4B] = $00   ; WX
// [$FFFF] = $00   ; IE
