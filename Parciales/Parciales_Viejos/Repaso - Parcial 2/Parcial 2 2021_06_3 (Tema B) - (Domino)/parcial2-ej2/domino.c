#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "domino.h"

struct _s_domino
{
    unsigned int num_up;
    unsigned int num_down;
};

static char mark(bool b)
{
    return b ? 'O' : ' ';
}

static void dump_num(int num)
{
    printf("      | %c     %c |\n",
           mark(num > 1), mark(num > 3));
    printf("      | %c  %c  %c |\n",
           mark(num > 5), mark(num % 2 == 1), mark(num > 5));
    printf("      | %c     %c |\n",
           mark(num > 3), mark(num > 1));
}

static void dump_double_num(int num)
{
    printf(" --------------------- \n");
    printf(" | %c  %c  %c ", mark(num > 3), mark(num > 5), mark(num > 1));
    printf("| %c  %c  %c |\n", mark(num > 3), mark(num > 5), mark(num > 1));

    printf(" |    %c    ", mark(num % 2 == 1));
    printf("|    %c    |\n", mark(num % 2 == 1));

    printf(" | %c  %c  %c ", mark(num > 1), mark(num > 5), mark(num > 3));
    printf("| %c  %c  %c |\n", mark(num > 1), mark(num > 5), mark(num > 3));
    printf(" --------------------- \n");
}

void dump(int num_up, int num_down)
{
    /* Pretty dump funcion for cool visualization :) */
    if (num_up != num_down)
    {
        printf("      ----------- \n");
        dump_num(num_up);
        printf("      |---------| \n");
        dump_num(num_down);
        printf("      ----------- \n");
    }
    else
    {
        dump_double_num(num_up);
    }
}

/* Representation invariant */

static bool invrep(domino p)
{
    bool valid_domino = p != NULL && p->num_up <= 6 && p->num_down <= 6;
    return valid_domino;
}

/* Public functions */

domino domino_new(int num_up, int num_down)
{
    domino p = malloc(sizeof(struct _s_domino));
    p->num_up = num_up;
    p->num_down = num_down;
    assert(invrep(p));
    return p;
}

bool domino_is_double(domino p)
{
    assert(invrep(p));
    return p->num_down == p->num_up;
}

bool domino_eq(domino p1, domino p2)
{
    assert(invrep(p1) && invrep(p2));
    bool equals = false;
    if (p1->num_up == p2->num_up && p1->num_down == p2->num_down)
    {
        equals = true;
    }
    else if (p1->num_up == p2->num_down && p1->num_down == p2->num_up)
    {
        equals = true;
    }
    assert(invrep(p1) && invrep(p2));
    return equals;
}

bool domino_matches(domino p_top, domino p_bottom)
{
    assert(invrep(p_top) && invrep(p_bottom));
    return p_top->num_down == p_bottom->num_up;
}

domino domino_flip(domino p)
{
    assert(invrep(p));
    unsigned int aux = p->num_up;
    p->num_up = p->num_down;
    p->num_down = aux;
    assert(invrep(p));
    return p;
}

void domino_dump(domino p)
{
    assert(invrep(p));
    dump(p->num_up, p->num_down);
    assert(invrep(p));
}

domino domino_destroy(domino p)
{
    assert(invrep(p));
    free(p);
    p = NULL;
    return p;
}
