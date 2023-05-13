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

// Funcion auxiliar para chequear si se inicializo la tupla principal del stack.
static void is_initialized_stack(stack s);

// Funcion auxiliar para chequear despues de un malloc que se halla podido reservar la memoria.
static void check_malloc(void *p);

stack stack_empty()
{
    stack s = NULL;
    s = malloc(sizeof(struct _s_stack));
    check_malloc(s);
    s->elems = malloc(sizeof(stack_elem));
    check_malloc(s->elems);
    s->capacity = 1u;
    s->size = 0u;

    return s;
}

stack stack_push(stack s, stack_elem e)
{
    is_initialized_stack(s);
    if (s->size == s->capacity) // Aumentamos el espacio reservado si es necesario
    {
        s->capacity = 2u * (s->capacity);
        s->elems = realloc(s->elems, s->capacity * sizeof(stack_elem));
        check_malloc(s->elems);
    }
    assert(s->elems != NULL && s->capacity > s->size);
    s->size = s->size + 1u;
    s->elems[s->size - 1u] = e;
    return s;
}

stack stack_pop(stack s)
{
    is_initialized_stack(s);
    if (s->size > 0)
    {
        s->size--;
    }
    return s;
}

unsigned int stack_size(stack s)
{
    is_initialized_stack(s);
    return s->size;
}

stack_elem stack_top(stack s)
{
    is_initialized_stack(s);
    assert(!stack_is_empty(s));
    return s->elems[s->size - 1];
}

bool stack_is_empty(stack s)
{
    is_initialized_stack(s);
    return (s->size == 0);
}

stack_elem *stack_to_array(stack s)
{
    is_initialized_stack(s);
    unsigned int length = stack_size(s);
    stack_elem *array = NULL;
    if (length != 0)
    {
        array = malloc(sizeof(stack_elem) * length);
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

stack_elem *stack_array_destroy(stack_elem *a)
{
    free(a);
    return NULL;
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

static void is_initialized_stack(stack s)
{
    if (s == NULL)
    {
        fprintf(stderr, "Error, uninitialized stack.\n");
        exit(EXIT_FAILURE);
    }
}

static void check_malloc(void *p)
{
    if (p == NULL)
    {
        fprintf(stderr, "Not enouht memory .\n");
        exit(EXIT_FAILURE);
    }
}