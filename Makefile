# ==========================================
#   Unity Project - A Test Framework for C
#   Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
#   [Released under MIT License. Please refer to license.txt for details]
# ==========================================
C_COMPILER=clang
UNITY_ROOT=Unity

CFLAGS=-std=c99
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition
# CFLAGS += -Werror

TARGET_BASE1=all_tests
TARGET1 = $(TARGET_BASE1).out


-include ./make_sources

HOST_OUTPUT=gb.out
HOST_SRC=$(SRC_FILES)\
        src/host/main.c\
        src/host/lcd.c\
				src/host/keyboard.c\
				src/host/serial.c\
				src/host/cart.c


HOST_INC=$(INC_FILES)

TEST_OUTPUT=unit_test.out
TEST_SRC=$(SRC_FILES)\
	src/host/keyboard.c\
	src/host/serial.c\
	src/host/cart.c\
  $(UNITY_ROOT)/src/unity.c \
  $(UNITY_ROOT)/extras/fixture/src/unity_fixture.c \
  test/test_instructions.c \
  test/test_cpu.c \
  test/test_memory.c \
  test/test_cart.c \
  test/test_timer.c\
  test/test_boot.c \
  test/test_runners/testrunner_instructions.c \
  test/test_runners/testrunner_cpu.c \
  test/test_runners/testrunner_cart.c \
  test/test_runners/testrunner_boot.c \
  test/test_runners/testrunner_memory.c \
  test/test_runners/testrunner_timer.c\
  test/test_runners/all_tests.c

TEST_INC=$(INC_FILES)\
         -I$(UNITY_ROOT)/src \
         -I$(UNITY_ROOT)/extras/fixture/src

SYMBOLS=

default:
	$(C_COMPILER) $(CFLAGS) $(TEST_INC) -DDEBUG=0 -DTRACE=0 -DBOOT_ROM=1 -DUNITTEST=1 $(SYMBOLS) $(TEST_SRC) -o $(TEST_OUTPUT)
	- ./$(TEST_OUTPUT) -v

host:
	$(C_COMPILER) $(CFLAGS) $(HOST_INC) -DDEBUG=0 -DTRACE=0 -DBOOT_ROM=0 -lSDL2 $(SYMBOLS) $(HOST_SRC) -o $(HOST_OUTPUT)

target:
	$(MAKE) -f Makefile_target

download:
	$(MAKE) -f Makefile_target download

clean:
	rm -f $(TARGET1)
	rm -f $(HOST_OUTPUT)
	$(MAKE) -f Makefile_target clean
ci: CFLAGS += -Werror
ci: default
