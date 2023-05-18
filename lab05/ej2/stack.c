#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

struct _s_stack
{
    stack_elem *elems;     // Arreglo de elementos
    unsigned int size;     // Cantidad de elementos en la pila
    unsigned int capacity; // Capacidad actual del arreglo elems
};

bool inv_rep(stack s)
{
    bool b = (s != NULL) && (s->size <= s->capacity);
    return b;
}

// Funcion auxiliar para chequear despues de un malloc que se halla podido reservar la memoria.
static void check_alloc(void *p)
{
    if (p == NULL)
    {
        fprintf(stderr, "Not enouht memory .\n");
        exit(EXIT_FAILURE);
    }
}

stack stack_empty()
{
    stack s = NULL;
    s = malloc(sizeof(struct _s_stack));
    check_alloc(s);
    s->elems = malloc(sizeof(stack_elem));
    check_alloc(s->elems);
    s->capacity = 1u;
    s->size = 0u;

    return s;
}

stack stack_push(stack s, stack_elem e)
{
    assert(inv_rep(s));
    if (s->size == s->capacity) // Aumentamos el espacio reservado si es necesario
    {
        s->capacity = 2u * (s->capacity);
        s->elems = realloc(s->elems, s->capacity * sizeof(stack_elem));
        check_alloc(s->elems);
    }
    assert(s->elems != NULL && s->capacity > s->size);
    s->size = s->size + 1u;
    s->elems[s->size - 1u] = e;
    return s;
}

stack stack_pop(stack s)
{
    assert(inv_rep(s));
    if (s->size > 0)
    {
        s->size--;
    }
    return s;
}

unsigned int stack_size(stack s)
{
    assert(inv_rep(s));
    return s->size;
}

stack_elem stack_top(stack s)
{
    assert(inv_rep(s));
    assert(!stack_is_empty(s));
    return s->elems[s->size - 1];
}

bool stack_is_empty(stack s)
{
    assert(inv_rep(s));
    return (s->size == 0);
}

stack_elem *stack_to_array(stack s)
{
    assert(inv_rep(s));
    unsigned int length = stack_size(s);
    stack_elem *array = NULL;
    if (length != 0)
    {
        array = calloc(length, sizeof(stack_elem));
    }
    if (array == NULL && length > 0)
    {
        printf("Not enouht memory \n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < s->size; i++)
    {
        array[i] = s->elems[i];
    }
    return array;
}

stack stack_destroy(stack s)
{
    if (s != NULL)
    {
        free(s->elems);
    }
    free(s);
    return NULL;
}
