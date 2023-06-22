#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack
{
    unsigned int size;
    struct s_node *first;
};

struct s_node
{
    pstack_elem elem;
    priority_t priority;
    struct s_node *next;
};

static struct s_node *create_node(pstack_elem e, priority_t priority)
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

static bool invrep(pstack s)
{
    bool check = true;
    unsigned int check_size = 0;
    struct s_node *cursor = NULL;
    if (s == NULL)
    {
        check = false;
    }
    else if (s->size == 0)
    {
        check = s->first == NULL;
    }
    else
    {
        cursor = s->first;
        ++check_size;
        while (cursor->next != NULL && check)
        {
            check = check && cursor->priority >= cursor->next->priority;
            cursor = cursor->next;
            ++check_size;
        }
    }
    return check && check_size == s->size;
}

pstack pstack_empty(void)
{
    pstack s = malloc(sizeof(struct s_pstack));
    assert(s != NULL);
    s->size = 0;
    s->first = NULL;
    assert(invrep(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority)
{
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority), *cursor = NULL;
    if (pstack_is_empty(s))
    {
        s->first = new_node;
    }
    else if (s->first->priority <= priority)
    {
        new_node->next = s->first;
        s->first = new_node;
    }
    else
    {
        cursor = s->first;
        while (cursor->next != NULL && cursor->next->priority > priority)
        {
            cursor = cursor->next;
        }
        new_node->next = cursor->next;
        cursor->next = new_node;
    }
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
    assert(invrep(s));
    return s->first->elem;
}

priority_t pstack_top_priority(pstack s)
{
    assert(invrep(s));
    return s->first->priority;
}

unsigned int pstack_size(pstack s)
{
    assert(invrep(s));
    unsigned int size = s->size;
    return size;
}

pstack pstack_pop(pstack s)
{
    assert(invrep(s) && !pstack_is_empty(s));
    struct s_node *killme = s->first;
    s->first = s->first->next;
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
    s->first = NULL;
    free(s);
    s = NULL;
    return s;
}
