CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic -fsanitize=address
TARGET_INT = vector_test_int

$(TARGET_INT): test_int.c vector_int.c vector.h
	$(CC) $(CFLAGS) -o $(TARGET_INT) test_int.c vector_int.c

clean:
	rm -f $(TARGET_INT)

test: $(TARGET_INT)
	./$(TARGET_INT)

.PHONY: clean test