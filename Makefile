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
CFLAGS += -Werror

TARGET_BASE1=all_tests
TARGET1 = $(TARGET_BASE1).out

SRC_FILES=src/instructions/instructions.c \
					src/cpu.c\
					src/memory.c

TEST_FILES=\
  $(UNITY_ROOT)/src/unity.c \
  $(UNITY_ROOT)/extras/fixture/src/unity_fixture.c \
  test/test_instructions.c \
  test/test_cpu.c \
  test/test_memory.c \
  test/test_runners/testrunner_instructions.c \
  test/test_runners/testrunner_cpu.c \
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

all: clean default

clean:
	rm -f $(TARGET1)

ci: CFLAGS += -Werror
ci: default
