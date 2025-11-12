CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -fsanitize=address
TARGET = bracket_check
TEST_TARGET = test_brackets

SOURCES = main.c bracket_check.c
TEST_SOURCES = test.c bracket_check.c

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

$(TEST_TARGET): $(TEST_SOURCES)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SOURCES)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: all test clean