

//// Makefile

// Ejemplo 1:

CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = stack.c hanoi.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = solve-hanoi

.PHONY: clean

all: $(TARGET)  // cuando se hace "$ make" sin nada mas, se ejecuta all

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:    //    "$ make clean"
	$(RM) $(OBJECTS) $(TARGET)



/*abajo de clean... no se usan espacios, se usan Tads*/






// Ejemplo 2:

CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g

all: dict

dict: dict.o abb.o
	gcc -o dict dict.o sbb.o

abb.o: abb.c abb.h
	gcc -c $(CFLAGS) abb.c abb.h

clean:
	rm -rf *.o dict



// Idea:

para no ejecutar siempre -g hacer un comando como "$ make g" que compile para debuguear. 




   
