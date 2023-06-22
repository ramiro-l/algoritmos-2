#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue
{
    unsigned int size;
    priority_t min_priority;
    struct s_node **array;
};

struct s_node
{
    pqueue_elem elem;
    struct s_node *next;
};

static struct s_node *create_node(pqueue_elem e)
{
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node)
{
    assert(node != NULL);
    node->next = NULL;
    free(node);
    node = NULL;
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
    else
    {
        for (size_t i = 0; i <= q->min_priority; i++)
        {
            cursor = q->array[i];
            while (cursor != NULL)
            {
                cursor = cursor->next;
                ++check_size;
            }
        }
    }

    return check && check_size == q->size;
}

pqueue pqueue_empty(priority_t min_priority)
{
    pqueue q = malloc(sizeof(struct s_pqueue));
    assert(q != NULL);
    q->size = 0;
    q->min_priority = min_priority;
    q->array = malloc(sizeof(struct s_node *) * (1 + min_priority));
    for (size_t i = 0; i <= min_priority; i++)
    {
        q->array[i] = NULL;
    }
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority)
{
    assert(invrep(q));
    struct s_node *new_node = create_node(e), *cursor = NULL;
    if (q->array[priority] == NULL)
    {
        q->array[priority] = new_node;
    }
    else
    {
        cursor = q->array[priority];
        while (cursor->next != NULL)
        {
            cursor = cursor->next;
        }
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
    assert(invrep(q) && !pqueue_is_empty(q));
    unsigned int i = 0;
    while (q->array[i] == NULL)
    {
        ++i;
    }
    return q->array[i]->elem;
}

priority_t pqueue_peek_priority(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    unsigned int i = 0;
    while (q->array[i] == NULL)
    {
        ++i;
    }
    return i;
}

size_t pqueue_size(pqueue q)
{
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    struct s_node *killme = NULL;
    unsigned int i = 0;
    while (q->array[i] == NULL)
    {
        ++i;
    }
    killme = q->array[i];
    q->array[i] = q->array[i]->next;
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
    free(q->array);
    q->array = NULL;
    free(q);
    q = NULL;
    return q;
}
