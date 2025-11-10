CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -g -fsanitize=address
LDFLAGS = -fsanitize=address

all: converter tests

converter: main.c converter.c converter.h
	$(CC) $(CFLAGS) -o converter main.c converter.c $(LDFLAGS)

tests: test.c converter.c converter.h
	$(CC) $(CFLAGS) -o tests test.c converter.c $(LDFLAGS)

clean:
	rm -f converter tests

run: converter
	./converter

test: tests
	./tests

.PHONY: all clean run test