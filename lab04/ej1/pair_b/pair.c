#include <stdio.h>
#include <stdlib.h>
#include "pair.h"

pair_t pair_new(int x, int y)
{
    pair_t res = NULL;
    res = malloc(sizeof(struct s_pair_t));
    res->fst = x;
    res->snd = y;
    return res;
}

int pair_first(pair_t p)
{
    return p->fst;
}

int pair_second(pair_t p)
{
    return p->snd;
}

pair_t pair_swapped(pair_t p)
{
    pair_t res = NULL;
    res = malloc(sizeof(struct s_pair_t));
    res->fst = p->snd;
    res->snd = p->fst;
    return res;
}

pair_t pair_destroy(pair_t p)
{
    free(p);
    return p;
}
