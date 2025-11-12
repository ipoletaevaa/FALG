CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -fsanitize=address
BUILD_DIR = build

SOURCES = main.c bracket_check.c
TEST_SOURCES = test.c bracket_check.c

OBJECTS = $(SOURCES:%.c=$(BUILD_DIR)/%.o)
TEST_OBJECTS = $(TEST_SOURCES:%.c=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR) lab6 tests

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

lab6: $(OBJECTS)
	$(CC) $(CFLAGS) -o lab6 $(OBJECTS)

tests: $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o tests $(TEST_OBJECTS)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: tests
	./tests

clean:
	rm -rf $(BUILD_DIR) lab6 tests

.PHONY: all test clean