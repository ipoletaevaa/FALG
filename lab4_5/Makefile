CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -Iinclude -fsanitize=address -g
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

SOURCES = $(SRC_DIR)/heap.c $(SRC_DIR)/letter.c $(SRC_DIR)/post_office.c \
          $(SRC_DIR)/graph.c $(SRC_DIR)/simulation.c

MAIN_SOURCE = main.c

TEST_SOURCES = $(TEST_DIR)/test_heap.c $(TEST_DIR)/test_simulation.c

OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o) $(BUILD_DIR)/main.o
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.c=$(BUILD_DIR)/%.o)

TARGET = mail_system
TEST_TARGET = test_heap
TEST_SIM_TARGET = test_simulation

.PHONY: all clean test test_all

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/main.o: $(MAIN_SOURCE) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

test: $(TEST_TARGET) $(TEST_SIM_TARGET)
	./$(TEST_TARGET)
	./$(TEST_SIM_TARGET)

test_all: test

$(TEST_TARGET): $(BUILD_DIR)/test_heap.o $(filter-out $(BUILD_DIR)/main.o $(BUILD_DIR)/test_simulation.o, $(OBJECTS))
	$(CC) $(CFLAGS) -o $@ $^

$(TEST_SIM_TARGET): $(BUILD_DIR)/test_simulation.o $(filter-out $(BUILD_DIR)/main.o $(BUILD_DIR)/test_heap.o, $(OBJECTS))
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_TARGET) $(TEST_SIM_TARGET)

run: $(TARGET)
	./$(TARGET) connections.txt simulation.log

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET) connections.txt simulation.log
