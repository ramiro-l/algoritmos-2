#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int *y)
{
    if (x >= 0)
    {
        *y = x;
    }
    else
    {
        *y = -x;
    }
}

int main(void)
{
    int a = 0, res = 0; // No modificar esta declaración
    int *p = &res;
    a = -10;

    absolute(a, p);

    printf("%d \n", res);

    return EXIT_SUCCESS;
}

/*
El parámetro int *y de absolute() es de tipo in, de tipo out o de tipo in/out ?
 -> Es de tipo in/out , porque puedo leerlo y escribirlo.

¿Qué tipo de parámetros tiene disponibles C para sus funciones?
 -> Tiene solo el tipo in/out porque para poder leerlo si o si nececito la direccion de memoria y viceversa para editarlo
    por lo tanto siempre voy a poder editarlo y leerlo.

*/