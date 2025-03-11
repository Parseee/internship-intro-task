.PHONY: all clean build clean_bin clean_obj rebuild

PROJECT_NAME = task4

SRC_DIR = ./src
BUILD_DIR = ./build
CC = gcc
UNAME = $(shell uname -s)
ifeq ($(UNAME), Darwin) # I'm uisng mac and alternative version of gcc
	CC = gcc-14
endif

CFLAGS =-Wall -Wextra -Waggressive-loop-optimizations -g -std=c11 \
		-Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts \
		-Wconversion -Wempty-body -Wfloat-equal \
		-Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op \
		-Wopenmp-simd -Wpacked -Wpointer-arith -Winit-self \
		-Wredundant-decls -Wshadow -Wsign-conversion \
		-Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods \
		-Wsuggest-final-types -Wswitch-default -Wswitch-enum -Wsync-nand \
		-Wundef -Wunreachable-code -Wunused -Wvariadic-macros \
		-Wno-missing-field-initializers -Wno-narrowing -Wno-varargs \
		-Wstack-protector -fcheck-new -fstack-protector -fstrict-overflow \
		-fno-omit-frame-pointer -Wlarger-than=81920 -Wstack-usage=81920 \
		-Werror=vla -fsanitize=leak

SOURCES = main.c
SOURCES_REL_PATH = $(patsubst %.c,$(SRC_DIR)/%.c,$(SOURCES))

DIRS = .
BUILD_DIRS = $(DIRS:%=$(BUILD_DIR)/%)

OBJECTS = $(patsubst %.c,%.o,$(SOURCES))
OBJECTS_REL_PATH = $(patsubst %.o,$(BUILD_DIR)/%.o,$(OBJECTS))
DEPS_REL_PATH = $(OBJECTS_REL_PATH:%.o=%.d)

INCLUDES = 
LIBS =

all: build run

build: $(PROJECT_NAME).out

run:
	@./$(PROJECT_NAME).out


$(PROJECT_NAME).out: $(OBJECTS_REL_PATH)
	@$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIRS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIRS):
	@mkdir -p $@

-include $(DEPS_REL_PATH)

clean: clean_bin clean_obj clean_lib

clean_bin:
	rm -rf $(PROJECT_NAME).out

clean_obj:
	rm -rf ./build

rebuild: clean build
