#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "list.h"

struct _list
{
    list_elem elem;
    struct _list *next;
};

list empty(void)
{
    list p = NULL;
    return p;
}

list addl(list l, list_elem e)
{
    list p = NULL;
    p = malloc(sizeof(struct _list));
    p->elem = e;
    p->next = l;
    l = p;
    return l;
}

/* Operations */

bool is_empty(list l)
{
    return l == NULL;
}

list_elem head(list l)
{
    assert(!is_empty(l));
    list_elem res = l->elem;
    return res;
}

list tail(list l)
{
    assert(!is_empty(l));
    list p = l;
    l = l->next;
    free(p);
    return l;
}

list addr(list l, list_elem e)
{
    list q, p = l;
    q = malloc(sizeof(struct _list));
    q->elem = e;
    q->next = NULL;
    if (!is_empty(l))
    {
        p = l;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = q;
    }
    else
    {
        l = q;
    }
    return l;
}

unsigned int length(list l)
{
    unsigned int n = 0;
    list p = l;
    while (p != NULL)
    {
        p = p->next;
        n++;
    }
    return n;
}

list concat(list l1, list l2)
{
    list p;
    if (!is_empty(l1))
    {
        p = l1;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = l2;
    }
    else
    {
        l1 = l2;
    }
    return l1;
}

list_elem index(list l, unsigned int n)
{
    assert(length(l) > n);
    list_elem e;
    unsigned int i = 0u;
    list p = l;
    while (i < n)
    {
        p = p->next;
        i++;
    }
    e = p->elem;
    return e;
}

list take(list l, unsigned int n)
{
    unsigned int i = 0u;
    list q;
    list p = l;
    while (p != NULL)
    {
        if (i > n)
        {
            q = p;
            p = p->next;
            free(q);
        }
        else
        {
            p = p->next;
        }
        i++;
    }
    return l;
}

list drop(list l, unsigned int n)
{
    unsigned int i = 0u;
    list q;
    list p = l;
    while (p != NULL)
    {
        if (i <= n)
        {
            q = p;
            p = p->next;
            free(q);
        }
        else
        {
            p = p->next;
        }
        i++;
    }
    return l;
}

list copy_list(list l)
{
    list l2, p, q, h;
    if (!is_empty(l))
    {
        p = l; // Inicializamos p,  para que sea igual a l

        // Agregamos el primer elemento porque sabemos que la lista es no vacia.
        q = malloc(sizeof(struct _list));
        q->elem = p->elem;
        q->next = NULL;

        l2 = q;      // Asignamos a la copia la direccion del primer elemento
        p = p->next; // Avanzamos uno porque ya lo agregamos.

        
        // Idea: l2 -> q -> h -> q -> h -> q ... -> NULL
        while (p != NULL)
        {
            if (q->next == NULL) // Agregamos h como el siguiente de la lista
            {
                h = malloc(sizeof(struct _list));
                h->elem = p->elem;
                h->next = NULL;
                q->next = h; // Al anterior le ponemos la direccion del nuevo elemento
            }
            else if (h->next == NULL) // Agregamos q como el siguiente de la lista
            {
                q = malloc(sizeof(struct _list));
                q->elem = p->elem;
                q->next = NULL;
                h->next = q; // Al anterior le ponemos la direccion del nuevo elemento
            }

            p = p->next; // Avanzo al siguiente elemento
        }
    }
    else
    {
        l2 = NULL;
    }

    
    return l2;
}

/* Destroy */

list destroy_list(list l)
{
    list p, q;
    p = l;
    while (p != NULL)
    {
        q = p;
        p = p->next;
        free(q);
    }
    return l;
}