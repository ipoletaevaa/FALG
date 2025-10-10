CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -Iinclude
TARGET = lab7
SOURCES = src/file_utils.c src/number_processor.c src/validation.c main.c
OBJECTS = $(SOURCES:.c=.o)
LDFLAGS = -fsanitize=address 

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

test: $(TARGET)
	@echo "Running tests..."
	@echo "101 1A zz 0 FF   123" > test1.txt
	@echo "ABC   45G" >> test1.txt
	./$(TARGET) test1.txt output.txt
	@cat output.txt
	@rm -f test1.txt output.txt

.PHONY: all clean test