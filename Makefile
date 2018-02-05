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
					src/memory.c\
					src/std_codes.c\
					src/host/cart.c\
					src/emulator.c\
					src/ppu.c\
					src/prefix_codes.c

APP_SRC=$(SRC_FILES)\
				src/main.c \

APP_INC=-Isrc \
				-Isrc/instructions

TEST_FILES=\
  $(UNITY_ROOT)/src/unity.c \
  $(UNITY_ROOT)/extras/fixture/src/unity_fixture.c \
  test/test_instructions.c \
  test/test_cpu.c \
  test/test_memory.c \
  test/test_cart.c \
  test/test_boot.c \
  test/test_runners/testrunner_instructions.c \
  test/test_runners/testrunner_cpu.c \
  test/test_runners/testrunner_cart.c \
  test/test_runners/testrunner_boot.c \
  test/test_runners/testrunner_memory.c \
  test/test_runners/all_tests.c


INC_DIRS=-Isrc \
         -Isrc/instructions \
         -I$(UNITY_ROOT)/src \
         -I$(UNITY_ROOT)/extras/fixture/src \

SYMBOLS=

default:
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES) $(TEST_FILES) -o $(TARGET1)
	- ./$(TARGET1) -v

run:
	$(C_COMPILER) $(CFLAGS) $(APP_INC) -DDEBUG=1 $(SYMBOLS) $(APP_SRC) -o $(APP_TARGET)
	- ./$(APP_TARGET) -v

sdl:
	gcc $(HOST_SRC) -lSDL2 -o $(HOST_APP)
	- ./$(HOST_APP)

all: clean default run


clean:
	rm -f $(TARGET1)
	rm -f $(APP_TARGET)

ci: CFLAGS += -Werror
ci: default
