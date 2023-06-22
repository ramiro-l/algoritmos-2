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
    float average_grade;
    unsigned int approved_courses;
    float priority;
    struct s_node *next;
};

static float calculate_priority(float average_grade,
                                unsigned int approved_courses)
{
    return 0.3 * (average_grade / MAX_GRADE) + 0.7 * (approved_courses / TOTAL_COURSES);
}

static struct s_node *create_node(pstack_elem e,
                                  float average_grade,
                                  unsigned int approved_courses)
{
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->average_grade = average_grade;
    new_node->approved_courses = approved_courses;
    new_node->priority = calculate_priority(average_grade, approved_courses);
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
            ++check_size;
            cursor = cursor->next;
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

pstack pstack_push(pstack s,
                   pstack_elem e,
                   float average_grade,
                   unsigned int approved_courses)
{
    assert(invrep(s));
    struct s_node *new_node = create_node(e, average_grade, approved_courses), *cursor = NULL;
    if (pstack_is_empty(s))
    {
        s->first = new_node;
    }
    else if (s->first->priority <= new_node->priority)
    {
        new_node->next = s->first;
        s->first = new_node;
    }
    else
    {
        cursor = s->first;
        while (cursor->next != NULL && cursor->next->priority > new_node->priority)
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

float pstack_top_average_grade(pstack s)
{
    assert(invrep(s));
    return s->first->average_grade;
}

unsigned int pstack_top_approved_courses(pstack s)
{
    assert(invrep(s));
    return s->first->approved_courses;
}

float pstack_top_priority(pstack s)
{
    assert(invrep(s));
    return s->first->priority;
}

unsigned int pstack_size(pstack s)
{
    assert(invrep(s));
    return s->size;
}

pstack pstack_copy(pstack s)
{
    assert(invrep(s));
    pstack q = pstack_empty();
    struct s_node *cursorS = NULL, *cursorQ = NULL;
    q->size = s->size;
    if (!pstack_is_empty(s))
    {
        q->first = create_node(s->first->elem, s->first->average_grade, s->first->approved_courses);
        cursorQ = q->first;
        cursorS = s->first->next;
        for (size_t i = 1; i < s->size; i++)
        {
            cursorQ->next = create_node(cursorS->elem, cursorS->average_grade, cursorS->approved_courses);
            cursorQ = cursorQ->next;
            cursorS = cursorS->next;
        }
    }
    assert(invrep(s) && invrep(q));
    return q;
}

pstack pstack_pop(pstack s)
{
    assert(invrep(s));
    struct s_node *killme = NULL;
    if (!pstack_is_empty(s))
    {
        killme = s->first;
        s->first = s->first->next;
        killme = destroy_node(killme);
        --s->size;
    }
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
    free(s);
    s = NULL;
    return s;
}
