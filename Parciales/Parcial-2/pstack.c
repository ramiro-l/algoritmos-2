#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack
{
    unsigned int size;
    struct s_node *front;
};

struct s_node
{
    pstack_elem elem;
    float average_grade;
    unsigned int approved_courses;
    float priority;
    struct s_node *next;
};

static float calculate_priority(float average_grade,
                                unsigned int approved_courses)
{
    float res = 0.3 * (average_grade / MAX_GRADE) + 0.7 * (approved_courses / TOTAL_COURSES);
    return res;
}

static struct s_node *create_node(pstack_elem e,
                                  float average_grade,
                                  unsigned int approved_courses)
{
    struct s_node *new_node = NULL;
    float priority = calculate_priority(average_grade, approved_courses);
    new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->average_grade = average_grade;
    new_node->approved_courses = approved_courses;
    new_node->priority = priority;
    new_node->next = NULL;

    assert(new_node->elem == e && new_node->average_grade == average_grade &&
           new_node->approved_courses == approved_courses &&
           new_node->priority == priority &&
           new_node->next == NULL);

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
    struct s_node *aux = NULL;
    unsigned int size_check = 0;

    if (s == NULL)
    {
        check = false;
    }
    else if (s->size == 0)
    {
        check = s->front == NULL;
    }
    else
    {
        aux = s->front;
        for (size_t i = 0; (i < s->size - 1) && check; i++)
        {
            check = check && aux->priority == calculate_priority(aux->average_grade, aux->approved_courses);
            check = check && aux->priority >= aux->next->priority;
            ++size_check;

            aux = aux->next;
        }
        ++size_check;
        check = check && aux->next == NULL;
    }

    return check && s->size == size_check;
}

pstack pstack_empty(void)
{
    pstack s = NULL;
    s = malloc(sizeof(struct s_pstack));
    assert(s != NULL);
    s->size = 0;
    s->front = NULL;
    assert(s->size == 0 && s->front == NULL);
    return s;
}

pstack pstack_push(pstack s,
                   pstack_elem e,
                   float average_grade,
                   unsigned int approved_courses)
{
    assert(invrep(s));
    struct s_node *new_node = create_node(e, average_grade, approved_courses);
    struct s_node *aux = NULL;

    if (pstack_is_empty(s))
    {
        s->front = new_node;
        ++s->size;
    }
    else if (new_node->priority >= s->front->priority)
    {
        new_node->next = s->front;
        s->front = new_node;
        ++s->size;
    }
    else
    {
        aux = s->front;
        while (aux->next != NULL && new_node->priority < aux->next->priority)
        {
            aux = aux->next;
        }
        new_node->next = aux->next;
        aux->next = new_node;
        ++s->size;
    }

    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s)
{
    assert(invrep(s));
    return (s->size == 0 && s->front == NULL);
}

pstack_elem pstack_top(pstack s)
{
    assert(invrep(s) && !pstack_is_empty(s));
    return s->front->elem;
}

float pstack_top_average_grade(pstack s)
{
    assert(invrep(s) && !pstack_is_empty(s));
    return s->front->average_grade;
}

unsigned int pstack_top_approved_courses(pstack s)
{
    assert(invrep(s) && !pstack_is_empty(s));
    return s->front->approved_courses;
}

float pstack_top_priority(pstack s)
{
    assert(invrep(s) && !pstack_is_empty(s));
    return s->front->priority;
}

unsigned int pstack_size(pstack s)
{
    assert(invrep(s));
    unsigned int size = s->size;
    return size;
}

pstack pstack_copy(pstack s)
{
    assert(invrep(s));
    pstack copy = pstack_empty();
    struct s_node *aux_s = NULL, *aux_copy = NULL;
    if (!pstack_is_empty(s))
    {
        copy->size = s->size;

        aux_s = s->front;
        aux_copy = create_node(aux_s->elem, aux_s->average_grade, aux_s->approved_courses);
        copy->front = aux_copy;
        aux_s = aux_s->next;
        while (aux_s != NULL)
        {
            aux_copy->next = create_node(aux_s->elem, aux_s->average_grade, aux_s->approved_courses);
            aux_copy = aux_copy->next;
            aux_s = aux_s->next;
        }
    }
    assert(invrep(s) && invrep(copy) && (s->size == copy->size));
    return copy;
}

pstack pstack_pop(pstack s)
{
    assert(invrep(s));
    struct s_node *killme = NULL;
    if (!pstack_is_empty(s))
    {
        killme = s->front;
        s->front = s->front->next;
        killme = destroy_node(killme);
        --s->size;
    }
    assert(killme == NULL);
    return s;
}

pstack pstack_destroy(pstack s)
{
    assert(invrep(s));
    while (s->front != NULL)
    {
        s = pstack_pop(s);
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}
