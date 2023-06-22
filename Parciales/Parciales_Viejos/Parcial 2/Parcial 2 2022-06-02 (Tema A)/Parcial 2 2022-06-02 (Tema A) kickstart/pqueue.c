#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue
{
    unsigned int size;
    struct s_node *first;
};

struct s_node
{
    pqueue_elem elem;
    unsigned int priority;
    struct s_node *next;
};

static struct s_node *create_node(pqueue_elem e, unsigned int priority)
{
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node)
{
    assert(node != NULL);
    node->next = NULL;
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}

static bool invrep(pqueue q)
{
    bool check = true;
    unsigned int check_size = 0;
    struct s_node *cursor = NULL;
    if (q == NULL)
    {
        check = false;
    }
    else if (q->size == 0)
    {
        check = q->first == NULL;
    }
    else
    {
        cursor = q->first;
        ++check_size;
        while (cursor->next != NULL && check)
        {
            check = check && cursor->priority <= cursor->next->priority;
            ++check_size;
            cursor = cursor->next;
        }
    }
    return check && check_size == q->size;
}

pqueue pqueue_empty(void)
{
    pqueue q = malloc(sizeof(struct s_pqueue));
    assert(q != NULL);
    q->size = 0;
    q->first = NULL;
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority)
{
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    struct s_node *cursor = NULL;
    if (pqueue_is_empty(q))
    {
        q->first = new_node;
    }
    else if (q->first->priority > priority)
    {
        new_node->next = q->first;
        q->first = new_node;
    }
    else
    {
        cursor = q->first;
        while (cursor->next != NULL && cursor->next->priority <= priority)
        {
            cursor = cursor->next;
        }
        new_node->next = cursor->next;
        cursor->next = new_node;
    }

    ++q->size;
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q)
{
    assert(invrep(q));
    return q->size == 0;
}

pqueue_elem pqueue_peek(pqueue q)
{
    assert(invrep(q));
    return q->first->elem;
}

unsigned int pqueue_peek_priority(pqueue q)
{
    assert(invrep(q));
    return q->first->priority;
}

unsigned int pqueue_size(pqueue q)
{
    assert(invrep(q));
    unsigned int size = q->size;
    return size;
}

pqueue pqueue_dequeue(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    struct s_node *killme = q->first;
    q->first = q->first->next;
    killme = destroy_node(killme);
    --q->size;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q)
{
    assert(invrep(q));
    while (!pqueue_is_empty(q))
    {
        q = pqueue_dequeue(q);
    }
    q->first = NULL;
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
