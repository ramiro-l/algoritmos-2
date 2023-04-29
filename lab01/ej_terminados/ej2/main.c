/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

unsigned int array_from_stdin(int array[],
                              unsigned int max_size)
{
    unsigned int tamDelArreglo;
    printf("Ingrese el tamaño del arreglo:\t");
    fscanf(stdin, "%u", &tamDelArreglo); // Pide por consola  el tamaño del arreglo.
    if (tamDelArreglo < max_size)        // Revisa que el tamaño ingresado sea valido.
    {
        for (size_t i = 0; i < tamDelArreglo; i++) // Itera todo el tamaño del arreglo.
        {
            printf("Valor del lugar %ld:\t", i);
            fscanf(stdin, "%d", &array[i]); // Pide por consola que ingreses el elemento en la posicion i.
        }
    }
    else
    {
        printf("El tamaño del arreglo es muy grande.\n");
        exit(EXIT_FAILURE);
    }

    return tamDelArreglo;
}

void array_dump(int a[], unsigned int length)
{
    printf("[");

    for (unsigned int i = 0; i < length; ++i) // Recorre el arreglo
    {
        if (i == length - 1)
        {
            printf("%d", a[i]); // Imprimo el ultimo elemento sin la coma
        }
        else
        {
            printf("%d, ", a[i]); // Imprimo los elementos del arreglos
        }
    }

    printf("]\n");
}

int main(void)
{
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];

    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_stdin(array, MAX_SIZE);

    /*dumping the array*/
    array_dump(array, length);

    return EXIT_SUCCESS;
}
