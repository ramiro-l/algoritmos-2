#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"

static unsigned int partition(int a[], unsigned int izq, unsigned int der)
{
    unsigned int i, j, pivot;
    pivot = izq;
    i = izq + 1;
    j = der;
    while (i <= j)
    {
        if (goes_before(a[i], a[pivot])) // Si a[i] esta bien entonces avanza uno por izquierda sino revisa que pasa por derecha osea el a[j]
        {
            i++;
        }
        else if (goes_before(a[pivot], a[j])) // Si a[j] esta bien entonces retrocede uno por derecha sino ambos estan mal
        {
            j--;
        }
        else if (goes_before(a[pivot], a[i]) && goes_before(a[j], a[pivot])) // Si ambos elementos (a[j] y a[i]) estan mal los intercambia
        {
            swap(a, i, j);
            i++;
            j--;
        }
    }
    swap(a, pivot, j); // Posiciona el pivot donde tiene que estar
    pivot = j;

    return pivot;
}

static void quick_sort_rec(int a[], unsigned int izq, unsigned int der)
{
    unsigned int pivot;
    if (der > izq) // Siempre que existan elementos entre izq y der del array
    {
        pivot = partition(a, izq, der);                          // El elemento de la izq lo ondena de tal forma que a[izq..pivot] <= a[pivot] <= a[pivot..der] y guarda la posicion de pivot
        quick_sort_rec(a, izq, (pivot == 0u) ? 0u : pivot - 1u); // Ahora ordena hace la recursividad en a[izq..pivot-1] pero revisa que pivot - 1 no sea un numero negativo porque estamos trabajando con unsigned int
        quick_sort_rec(a, pivot + 1u, der);                      // Despues ordena con recursividad en a[pivot+1..der]
    }
}

void quick_sort(int a[], unsigned int length)
{
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}
