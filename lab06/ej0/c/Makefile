CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = main.c queue_helpers.c queue.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = queue

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full -s ./$(TARGET) ../input/unsorted-200000.in