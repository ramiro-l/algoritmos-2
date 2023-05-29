#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue
{
    unsigned int size;
    struct s_node *fst;
};

struct s_node
{
    pqueue_elem elem;
    unsigned int priority;
    struct s_node *next;
};

static struct s_node *create_node(pqueue_elem e, unsigned int priority)
{
    struct s_node *new_node = NULL;

    new_node = malloc(sizeof(struct s_node));

    assert(new_node != NULL);

    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;

    assert(new_node->elem == e && new_node->priority == priority && new_node->next == NULL);
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node)
{
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}

static bool invrep(pqueue q)
{
    bool res = true;
    struct s_node *new_node = NULL;
    if (q != NULL) // Si la estructura principal es distina de null, revisamos
    {
        if (q->size == 0) // Si el tamaño de la cola es 0, resvisamos
        {
            res = q->fst == NULL;
        }
        else // Revisamos que se cumpla que los elementos mantienen el orden de prioridad p1 <= .. <= pn
        {
            new_node = q->fst;
            for (size_t i = 0; i < q->size - 1; i++)
            {
                res = res && (new_node->priority <= new_node->next->priority);
                new_node = new_node->next;
            }
        }
    }
    else // Si la estructura principal es NULL, no es una pqueue porque no esta inicializada
    {
        res = false;
    }
    return res;
}

pqueue pqueue_empty(void)
{
    pqueue q = NULL;

    q = malloc(sizeof(struct s_pqueue));
    assert(q != NULL);

    q->size = 0;
    q->fst = NULL;

    assert(q != NULL && invrep(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority)
{
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    struct s_node *p = NULL;

    if (pqueue_is_empty(q))
    {
        q->fst = new_node;
        ++q->size; // Aumentamos el tamaño de la cola
    }
    else if (q->fst->priority <= priority)
    {
        p = q->fst;
        // Iteramos hasta que el siguiente de p tenga menor prioridad ( p->priority <= p->next->priority )
        while (p->next != NULL && p->next->priority <= priority)
        {
            p = p->next;
        }
        new_node->next = p->next;
        p->next = new_node;
        ++q->size; // Aumentamos el tamaño de la cola
    }
    else
    {
        new_node->next = q->fst;
        q->fst = new_node;
        ++q->size; // Aumentamos el tamaño de la cola
    }

    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q)
{
    assert(invrep(q));
    bool res = (q->size == 0 && q->fst == NULL);
    assert(invrep(q));
    return res;
}

pqueue_elem pqueue_peek(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue_elem elem = q->fst->elem;
    assert(invrep(q));
    return elem;
}

unsigned int pqueue_peek_priority(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue_elem p = q->fst->priority;
    assert(invrep(q));
    return p;
}

unsigned int pqueue_size(pqueue q)
{
    assert(invrep(q));
    unsigned int size = q->size;
    return size;
}

pqueue pqueue_dequeue(pqueue q)
{
    assert(invrep(q));
    struct s_node *killme = NULL;
    if (!pqueue_is_empty(q))
    {
        killme = q->fst;
        q->fst = q->fst->next;
        destroy_node(killme);
        --q->size;
    }
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q)
{
    assert(invrep(q));
    for (size_t i = 0; i < q->size; i++)
    {
        pqueue_dequeue(q);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
