#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"

struct s_node
{
    set_elem elem;
    struct s_node *next;
};

typedef struct s_node *node_t;

struct s_set
{
    unsigned int size;
    node_t first;
};

static bool invrep(set s)
{
    bool chek = true;
    unsigned int chek_size = 0;
    node_t aux = NULL;
    if (s == NULL)
    {
        chek = false;
    }
    else if (s->size == 0)
    {
        chek = s->first == NULL;
    }
    else
    {
        aux = s->first;
        ++chek_size;
        while (aux->next != NULL && chek)
        {
            chek = aux->elem < aux->next->elem;
            aux = aux->next;
            ++chek_size;
        }
    }

    return chek && chek_size == s->size;
}

static struct s_node *create_node(set_elem e)
{
    node_t new = malloc(sizeof(struct s_node));
    assert(new != NULL);
    new->elem = e;
    new->next = NULL;
    return new;
}

static struct s_node *destroy_node(struct s_node *node)
{
    assert(node != NULL);
    free(node);
    return node;
}

/* CONSTRUCTORS */

set set_empty(void)
{
    struct s_set *new = malloc(sizeof(struct s_set));
    assert(new != NULL);
    new->size = 0;
    new->first = NULL;
    assert(invrep(new));
    return new;
}

set set_add(set s, set_elem e)
{
    assert(invrep(s));
    struct s_node *new = NULL;
    node_t node = NULL;
    if (!set_member(e, s))
    {
        if (set_is_empty(s) || e < s->first->elem)
        {
            new = create_node(e);
            new->next = s->first;
            s->first = new;
            ++s->size;
        }
        else
        {
            node = s->first;
            while (node->next != NULL && (e > node->next->elem))
            {
                node = node->next;
            }
            new = create_node(e);
            new->next = node->next;
            node->next = new;
            ++s->size;
        }
    }

    assert(invrep(s) && !set_is_empty(s));
    return s;
}

/* OPERATIONS   */

unsigned int set_cardinal(set s)
{
    assert(invrep(s));
    return s->size;
}

bool set_is_empty(set s)
{
    assert(invrep(s));
    return s->size == 0 && s->first == NULL;
}

bool set_member(set_elem e, set s)
{
    assert(invrep(s));
    node_t node = s->first;
    while (node != NULL && node->elem < e)
    {
        node = node->next;
    }
    return node != NULL && node->elem == e;
}

set set_elim(set s, set_elem e)
{
    assert(invrep(s) && set_member(e, s));
    node_t node = NULL;
    node_t killme = NULL;
    if (!set_is_empty(s))
    {
        if ( e == s->first->elem)
        {
            killme = s->first;
            s->first = s->first->next;
            killme = destroy_node(killme);
            --s->size;
        }
        else
        {
            node = s->first;
            while (node->next != NULL && (e != node->next->elem))
            {
                node = node->next;
            }
            killme = node->next;
            node->next  = node->next->next;
            killme = destroy_node(killme);
            --s->size;
        }
    }
    assert(invrep(s) && !set_member(e, s));
    return s;
}

set_elem set_get(set s)
{
    assert(invrep(s) && !set_is_empty(s));
    return s->first->elem;
}

set_elem *set_to_array(set s)
{
    assert(invrep(s));
    set_elem *array = malloc(sizeof(set_elem) * s->size);
    node_t node = s->first;
    for (size_t i = 0; i < s->size; i++)
    {
        array[i] = node->elem;
        node = node->next;
    }
    assert(invrep(s));
    return array;
}

set set_destroy(set s)
{
    assert(invrep(s));
    while (!set_is_empty(s))
    {
        s = set_elim(s, set_get(s));
    }
    free(s);
    s = NULL;
    return s;
}
