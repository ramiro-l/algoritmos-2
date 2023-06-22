#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "pqueue.h"

struct s_pqueue
{
    unsigned int size;
    struct s_node *first;
};

struct s_node
{
    pqueue_elem elem;
    float average_grade;
    unsigned int approved_courses;
    float priority;
    struct s_node *next;
};

static float calculate_priority(float average_grade,
                                unsigned int approved_courses)
{
    return 0.5 * (average_grade / MAX_GRADE) + 0.5 * (approved_courses / TOTAL_COURSES);
}

static struct s_node *create_node(pqueue_elem e,
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
        while (cursor->next != NULL)
        {
            check = check && cursor->priority >= cursor->next->priority;
            cursor = cursor->next;
            ++check_size;
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
    assert(invrep(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q,
                      pqueue_elem e,
                      float average_grade,
                      unsigned int approved_courses)
{
    assert(invrep(q));
    struct s_node *new_node = create_node(e, average_grade, approved_courses), *cursor = NULL;
    if (pqueue_is_empty(q))
    {
        q->first = new_node;
    }
    else if (q->first->priority < new_node->priority)
    {
        new_node->next = q->first;
        q->first = new_node;
    }
    else
    {
        cursor = q->first;
        while (cursor->next != NULL && cursor->next->priority >= new_node->priority)
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
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->first->elem;
}

float pqueue_peek_average_grade(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->first->average_grade;
}

unsigned int pqueue_peek_approved_courses(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->first->approved_courses;
}

float pqueue_peek_priority(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->first->priority;
}

unsigned int pqueue_size(pqueue q)
{
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_copy(pqueue q)
{
    assert(invrep(q));
    pqueue p = pqueue_empty();
    struct s_node *cursorQ = NULL, *cursorP = NULL;
    p->size = q->size;

    if (!pqueue_is_empty(q))
    {
        p->first = create_node(q->first->elem, q->first->average_grade, q->first->approved_courses);
        cursorQ = q->first->next;
        cursorP = p->first;
        for (size_t i = 1; i < q->size; i++)
        {
            cursorP->next = create_node(cursorQ->elem, cursorQ->average_grade, cursorQ->approved_courses);
            cursorP = cursorP->next;
            cursorQ = cursorQ->next;
        }
    }
    assert(invrep(q) && invrep(p));
    return p;
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
    free(q);
    q = NULL;
    return q;
}
