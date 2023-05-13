#include <stdio.h>
#include <stdlib.h>
#include "hanoi.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./solve-hanoi <disk-count>\n");
        exit(EXIT_FAILURE);
    }
    int count = atoi(argv[1]);
    if (count < 0)
    {
        printf("Negative disk-count is not allowed\n");
        exit(EXIT_FAILURE);
    }
    if (count > 20)
    {
        printf("> 20 is too slow!\n");
        exit(EXIT_FAILURE);
    }
    hanoi_t hanoi = hanoi_init(count);
    hanoi_print(hanoi);
    hanoi_solve(hanoi);
    hanoi = hanoi_destroy(hanoi);
    return 0;
}

/*
    Encontre el memory leak porque habia una diferencia de N (cantidad de discos) entre los allocs y los free,
    entonces sospeche que no se estaban liberado bien la memoria de esos discos, que estan representados como elementos
    las pilas, al chequear el hanoi_destroy() me di cuenta que solo se hacia free de la tupla pero faltaba destruir las
    3 pilas que creamos. Ahora porque difiere en N la cantidad de los free y allocs, porque como maximo vamos a tener N discos entre
    las 3 pilas, que al finalizar el programa quedan en la ultima pila.

    Despues los errores sugian porque no es estaban inicializando las 3 pilas correctamente.  
*/