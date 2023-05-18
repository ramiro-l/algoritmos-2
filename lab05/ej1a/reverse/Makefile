CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = ../stack.c reverse.c array_helpers.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = reverse

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)
	gcc -Wall -Werror -Wextra -pedantic -std=c99 ../stack.o ../test.c -o test

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)
	$(RM) ./test