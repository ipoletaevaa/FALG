CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -Iinclude -fsanitize=address
LDFLAGS = -fsanitize=address
TARGET = lab8
SOURCES = src/input_processor.c src/number_converter.c src/validation.c main.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run