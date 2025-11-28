CC = gcc
CFLAGS = -Wall -Wextra -g -fsanitize=address
INCLUDES = -Iinclude

TARGET = main
TEST_TARGET = test_runner
BUILDDIR = build
SRCDIR = src
TESTDIR = tests

SRCS = $(SRCDIR)/linked_list.c $(SRCDIR)/liver.c $(SRCDIR)/queue.c $(SRCDIR)/stack.c $(SRCDIR)/undo_manager.c main.c
OBJS = $(BUILDDIR)/linked_list.o $(BUILDDIR)/liver.o $(BUILDDIR)/queue.o $(BUILDDIR)/stack.o $(BUILDDIR)/undo_manager.o $(BUILDDIR)/main.o

TEST_SRCS = $(SRCDIR)/linked_list.c $(SRCDIR)/liver.c $(SRCDIR)/queue.c $(SRCDIR)/stack.c $(SRCDIR)/undo_manager.c $(TESTDIR)/test_runner.c
TEST_OBJS = $(BUILDDIR)/linked_list.o $(BUILDDIR)/liver.o $(BUILDDIR)/queue.o $(BUILDDIR)/stack.o $(BUILDDIR)/undo_manager.o $(BUILDDIR)/test_runner.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR)/main.o: main.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR)/test_runner.o: $(TESTDIR)/test_runner.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(TESTDIR):
	mkdir -p $(TESTDIR)

clean:
	rm -rf $(BUILDDIR) $(TARGET) $(TEST_TARGET) test_data.txt result.txt test_file.txt test_output.txt

rebuild: clean $(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

build: $(TARGET)

test-data:
	echo "1 Ivanov Ivan Ivanovich 15 5 1990 M 50000.0" > test_data.txt
	echo "2 Petrova Maria Sergeevna 20 8 1985 W 60000.0" >> test_data.txt
	echo "3 Sidorov Alexey 10 12 1995 M 45000.0" >> test_data.txt

run: $(TARGET)
	./$(TARGET)

memory-check: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

.PHONY: clean rebuild test build test-data run memory-check