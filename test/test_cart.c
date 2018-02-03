#include "cart.h"
#include "unity.h"
#include "unity_fixture.h"
#include <string.h>


TEST_GROUP(Cart);

TEST_SETUP(Cart) {

}

TEST_TEAR_DOWN(Cart) {}

TEST(Cart, load) {
    uint8_t mem[256];
    mem[0] = 0;
    cart_load(mem, 256);
    TEST_ASSERT_EQUAL(0xC9, mem[1]);
}
