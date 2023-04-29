#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "array_helpers.h"

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath)
{
    FILE *fp = fopen(filepath, "r");
    unsigned int tam_arr;

    if (fp != NULL) // Revisa que no tenga errores en la lectura de archivo
    {
        fscanf(fp, "%u", &tam_arr); // Lee el primer elemento del archivo y lo asigna al tamaño del arreglo
        if (tam_arr <= max_size)    // Revisa que este tamaño del archivo sea correcto
        {
            for (unsigned int i = 0; i < tam_arr; ++i) // Recorre el archivo
            {
                if (fscanf(fp, "%d", &array[i]) != 1) // Revisa que los datos leidos sean correctos
                {
                    printf("Error con los datos del arreglo.\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else
        {
            printf("Error, el tamaño del arreglo es incorrecto.\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        printf("Error al cargar el archivo.\n");
        exit(EXIT_FAILURE);
    }

    fclose(fp); // Cierra el archivo

    return tam_arr;
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

bool array_is_sorted(int a[], unsigned int length)
{
    bool res = true;
    if (length >= 1) // revisa que el arreglo tenga mas de un elemento
    {
        for (size_t i = 0; i < (length - 1); i++)
        {
            res = res && (a[i] <= a[i + 1]); // revisa que el elemento en la posicion i sea meno o igual que el siguiente
        }
    }
    return res;
}

void array_swap(int a[], unsigned int i, unsigned int j) // Dado un array y dos índices i, j  intercambia los valores de dichas posiciones
{
    int aux = a[i]; // Agrego una variable auxialiar sino no se puede
    a[i] = a[j];
    a[j] = aux;
}

void array_reverse(int a[], unsigned int length)
{
    unsigned int i = 0;
    unsigned int j = length - 1;
    unsigned int mid = length / 2;

    while (i != mid)
    {
        array_swap(a, i, j);
        i++;
        j--;
    }
}