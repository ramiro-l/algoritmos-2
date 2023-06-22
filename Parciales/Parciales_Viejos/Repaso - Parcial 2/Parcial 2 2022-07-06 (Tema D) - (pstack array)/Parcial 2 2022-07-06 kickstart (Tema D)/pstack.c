#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack
{
    unsigned int size;
    priority_t max_priority;
    struct s_node **array;
};

struct s_node
{
    pstack_elem elem;
    struct s_node *next;
};

static struct s_node *create_node(pstack_elem e)
{
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    new_node->elem = e;
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node)
{
    assert(node != NULL);
    free(node);
    node = NULL;
    return node;
}

static bool invrep(pstack s)
{
    bool check = true;
    unsigned int check_size = 0;
    struct s_node *cursor = NULL;
    if (s == NULL)
    {
        check = false;
    }
    else
    {
        for (size_t i = 0; i <= s->max_priority; i++)
        {
            cursor = s->array[i];
            while (cursor != NULL)
            {
                cursor = cursor->next;
                ++check_size;
            }
        }
    }

    return check && check_size == s->size;
}

pstack pstack_empty(priority_t max_priority)
{
    pstack s = malloc(sizeof(struct s_pstack));
    assert(s != NULL);
    s->size = 0;
    s->max_priority = max_priority;
    s->array = malloc(sizeof(struct s_node *) * (max_priority + 1));
    for (size_t i = 0; i <= max_priority; i++)
    {
        s->array[i] = NULL;
    }
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority)
{
    assert(invrep(s));
    struct s_node *new = create_node(e);
    new->next = s->array[priority];
    s->array[priority] = new;
    ++s->size;
    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s)
{
    assert(invrep(s));
    return s->size == 0;
}

pstack_elem pstack_top(pstack s)
{
    assert(invrep(s) && !pstack_is_empty(s));
    unsigned int i = s->max_priority;
    while (s->array[i] == NULL)
    {
        --i;
    }
    assert(invrep(s));
    return s->array[i]->elem;
}

priority_t pstack_top_priority(pstack s)
{
    assert(invrep(s) && !pstack_is_empty(s));
    unsigned int i = s->max_priority;
    while (s->array[i] == NULL)
    {
        --i;
    }
    assert(invrep(s));
    return i;
}

size_t pstack_size(pstack s)
{
    assert(invrep(s));
    return s->size;
}

pstack pstack_pop(pstack s)
{
    assert(invrep(s) && !pstack_is_empty(s));
    unsigned int i = s->max_priority;
    struct s_node *killme = NULL;
    while (s->array[i] == NULL)
    {
        --i;
    }
    killme = s->array[i];
    s->array[i] = s->array[i]->next;
    killme = destroy_node(killme);
    --s->size;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s)
{
    assert(invrep(s));
    while (!pstack_is_empty(s))
    {
        s = pstack_pop(s);
    }
    free(s->array);
    s->array = NULL;
    free(s);
    s = NULL;
    return s;
}
