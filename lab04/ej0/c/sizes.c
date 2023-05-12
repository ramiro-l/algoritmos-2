#include <stdio.h>
#include <stdlib.h>

#include "data.h"

void print_data(data_t d)
{
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

int main(void)
{

    data_t messi = {"Leo Messi", 35, 169};
    print_data(messi);

    printf("name-size  : %lu bytes\n"
           "age-size   : %lu bytes\n"
           "height-size: %lu bytes\n"
           "data_t-size: %lu bytes\n"
           "sum_size : %lu bytes \n",
           sizeof(messi.name),
           sizeof(messi.age),
           sizeof(messi.height),
           sizeof(messi),
           sizeof(messi.name) + sizeof(messi.age) + sizeof(messi.height));

    return EXIT_SUCCESS;
}

/*
    ¿La suma de los miembros coincide con el total?
    No coincide, data_t ocupa: 40 bytes y  la suma de (name-size + age-size + height-size) = 38. Opcupa 2 bytes mas que la suma.
    Esto sucede por el paddin que hace c al compilar.

    ¿El tamaño del campo name depende del nombre que contiene?
    No depende del nombre porque simpre se reservan 1 byte por el tamaño del array (name_t) en este caso es NAME_MAXSIZE=30.
*/