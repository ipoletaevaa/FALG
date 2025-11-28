CC = gcc
CFLAGS = -Wall -Wextra -g -fsanitize=address
INCLUDES = -Iinclude

TARGET = main
BUILDDIR = build
SRCDIR = src

OBJS = $(BUILDDIR)/linked_list.o $(BUILDDIR)/liver.o $(BUILDDIR)/queue.o $(BUILDDIR)/stack.o $(BUILDDIR)/undo_manager.o $(BUILDDIR)/main.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(BUILDDIR)/linked_list.o: $(SRCDIR)/linked_list.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR)/liver.o: $(SRCDIR)/liver.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR)/queue.o: $(SRCDIR)/queue.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR)/stack.o: $(SRCDIR)/stack.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR)/undo_manager.o: $(SRCDIR)/undo_manager.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR)/main.o: main.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR) $(TARGET)

rebuild: clean $(TARGET)

.PHONY: clean rebuild
