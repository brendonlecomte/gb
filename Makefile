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

APP_TARGET=gb.out

HOST_SRC=src/gpu/test.c
HOST_APP=gpu.o

SRC_FILES=src/instructions/instructions.c \
            src/cpu.c\
            src/memory/memory.c\
						src/memory/dma.c\
            src/std_codes.c\
            src/host/cart.c\
            src/emulator.c\
            src/ppu/ppu.c\
						src/ppu/sprites.c\
						src/ppu/tiles.c\
            src/gb_timer.c\
            src/prefix_codes.c\
						src/host/keyboard.c\
						src/physical_cart.c

APP_SRC=$(SRC_FILES)\
        src/main.c\
        src/host/lcd.c\
				src/host/keyboard.c


APP_INC=-Isrc\
	   -Isrc/memory \
     -Isrc/instructions \
		 -Isrc/ppu/

TEST_FILES=$(SRC_FILES)\
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

INC_DIRS=$(APP_INC)\
         -I$(UNITY_ROOT)/src \
         -I$(UNITY_ROOT)/extras/fixture/src

SYMBOLS=

default:
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) -DDEBUG=0 -DTRACE=0 -DBOOT_ROM=1 -DUNITTEST=1 $(SYMBOLS) $(TEST_FILES) -o $(TARGET1)
	- ./$(TARGET1) -v

host:
	$(C_COMPILER) $(CFLAGS) $(APP_INC) -DDEBUG=0 -DTRACE=0 -DBOOT_ROM=0 -lSDL2 $(SYMBOLS) $(APP_SRC) -o $(APP_TARGET)

sdl:
	$(C_COMPILER) $(HOST_SRC) -lSDL2 -o $(HOST_APP)
	- ./$(HOST_APP)

all: clean default host


clean:
	rm -f $(TARGET1)
	rm -f $(APP_TARGET)

ci: CFLAGS += -Werror
ci: default
