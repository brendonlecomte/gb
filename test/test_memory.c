#include "memory.h"
#include "unity.h"
#include "unity_fixture.h"

memory_t test_mem;

TEST_GROUP(Memory);


TEST_SETUP(Memory)
{
    memory_init(&test_mem);
    test_mem.inBoot = false;
}

TEST_TEAR_DOWN(Memory)
{
}

TEST(Memory, init)
{
    TEST_ASSERT_EQUAL(0x31, test_mem.cart[0]);
    TEST_ASSERT_EQUAL(0x21, test_mem.cart[4]);
}

TEST(Memory, read8)
{
    memory_write8(&test_mem, 7, 0xCC);
    TEST_ASSERT_EQUAL(0xCC, memory_read8(&test_mem, 7));
}

TEST(Memory, read16)
{
    memory_write16(&test_mem, 2, 0x55AA);
    TEST_ASSERT_EQUAL(0x55AA, memory_read16(&test_mem, 2));
}


TEST(Memory, write8)
{
    memory_write8(&test_mem, 0x1234, 0xCC);
    TEST_ASSERT_EQUAL(0xCC, memory_read8(&test_mem, 0x1234));
}

TEST(Memory, write16)
{
    memory_write16(&test_mem, 0x892, 0x55AA);
    TEST_ASSERT_EQUAL(0x55AA, memory_read16(&test_mem, 0x892));
}

TEST(Memory, inboot)
{
    test_mem.inBoot = true;
    TEST_ASSERT_EQUAL(0x32, memory_read8(&test_mem, 7));
}
