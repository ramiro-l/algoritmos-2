#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der)
{
    unsigned int pivot;
    if (der > izq) // Simpre que existan elementos entre izq y der del array
    {
        pivot = partition(a, izq, der);                          // El elemento de la izq lo ondena de tal forma que a[izq..pivot] <= a[pivot] <= a[pivot..der] y guarda la posicion de pivot
        quick_sort_rec(a, izq, (pivot == 0u) ? 0u : pivot - 1u); // Ahora ordena hace la recursividad en a[izq..pivot-1] pero revisa que pivot - 1 no sea un numero negativo porque estamos trabajando con unsigned int
        quick_sort_rec(a, pivot + 1u, der);                      // Despues ordena con recursividad en a[pivot+1..der]
    }
}

void quick_sort(int a[], unsigned int length)
{
    quick_sort_rec(a, 0u, (length == 0u) ? 0u : length - 1u); // Caso base de la recursividad y revisa length - 1 no sea un numero negativo porque estamos trabajando con unsigned int
}
