#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
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
