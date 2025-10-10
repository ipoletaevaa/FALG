
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c99 -Iinclude
LDFLAGS = -lm
TARGET = lab4

SRC_DIR = src
INCLUDE_DIR = include

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/constants.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(SRC_DIR)/main.o: $(SRC_DIR)/main.c $(INCLUDE_DIR)/constants.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(SRC_DIR)/main.o

$(SRC_DIR)/constants.o: $(SRC_DIR)/constants.c $(INCLUDE_DIR)/constants.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/constants.c -o $(SRC_DIR)/constants.o

clean:
	rm -f $(TARGET) $(SRC_DIR)/*.o

rebuild: clean $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean rebuild run