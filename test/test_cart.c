#include "cart.h"
#include "unity.h"
#include "unity_fixture.h"
#include <string.h>
#include "memory.h"


TEST_GROUP(Cart);

TEST_SETUP(Cart) {

}

TEST_TEAR_DOWN(Cart) {}

TEST(Cart, load) {
    uint8_t mem[256];
    mem[0] = 0;
    cart_load();
    TEST_ASSERT_EQUAL(0xC3, cart_read(0));
}

TEST(Cart, header) {
  uint8_t mem[0x8000];
  mem[0] = 0;
  cart_load();
  cart_t *cart = (cart_t *)&mem[0x100];
  TEST_ASSERT_EQUAL_STRING("TETRIS", cart->title);
  TEST_ASSERT_EQUAL(0x0A, cart->header_checksum);
  TEST_ASSERT_EQUAL(0xBF16, cart->checksum);
}
