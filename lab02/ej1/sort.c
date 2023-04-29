#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"

static void insert(int a[], unsigned int i)
{
    /* El ciclo se ejecuta siempre y cuando tenga dos elementos para comprara (j>0) y
       como sabemos que los elementos hasta j - 1 estan ordenados revisamos que
       j sea menor que j-1 entonces los intercambiamos */
    while (i > 0 && goes_before(a[i], a[i - 1]))
    {
        swap(a, i - 1, i); // Intercambia i y i-1
        i--;
    }
}

void insertion_sort(int a[], unsigned int length)
{
    for (unsigned int i = 1u; i < length; ++i)
    {
        assert(array_is_sorted(a, i)); // Revisa la invariante, siempre se cumple que arreglo esta ordenado hasta la posicion i - 1
        insert(a, i);                  // Ordena el elemento en la posicion i
    }
}

/*
¿Qué relación implementa la función goes_before()?
La funcion goes_before() revisa que un elemento (x) este antes que otro (y).
¿Cuál es el criterio que usa?
En este caso revisa que el elemento x sea menor en valor absoluto a y.
*/