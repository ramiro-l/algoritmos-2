#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "counter.h"

struct _counter
{
    unsigned int count;
};

counter counter_init(void)
{
    counter res = NULL;
    res = malloc(sizeof(struct _counter));
    if (res == NULL)
    {
        fprintf(stderr, "Invalid array.\n");
        exit(EXIT_FAILURE);
    }
    res->count = 0u;
    assert(counter_is_init(res));
    return res;
}

void counter_inc(counter c)
{
    c->count = c->count + 1u;
}

bool counter_is_init(counter c)
{
    return (c->count == 0u);
}

void counter_dec(counter c)
{
    assert(!counter_is_init(c));
    c->count = c->count - 1u;
}

counter counter_copy(counter c)
{
    counter res = NULL;
    res = malloc(sizeof(struct _counter));
    if (res == NULL)
    {
        printf("Not enouht memory \n");
        exit(EXIT_FAILURE);
    }
    res->count = c->count;
    return res;
}

void counter_destroy(counter c)
{
    free(c);
}