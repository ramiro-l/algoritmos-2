#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "stack.h"

struct _s_stack
{
  stack_elem elem;
  struct _s_stack *next;
};

bool inv_rep(stack s)
{
  return (s != NULL);
}

stack stack_empty()
{
  stack p = NULL;
  return p;
}

stack stack_push(stack s, stack_elem e)
{
  stack p = NULL;
  p = malloc(sizeof(struct _s_stack));
  if (p == NULL)
  {
    printf("Not enouht memory \n");
    exit(EXIT_FAILURE);
  }

  p->elem = e;
  p->next = s;
  s = p;
  return s;
}

stack stack_pop(stack s)
{
  assert(inv_rep(s));
  stack p = s;
  s = s->next;
  free(p);
  p = NULL;
  return s;
}

unsigned int stack_size(stack s)
{
  unsigned int i = 0u;
  while (s != NULL)
  {
    s = s->next;
    i++;
  }
  return i;
}

stack_elem stack_top(stack s)
{
  assert(inv_rep(s));
  stack_elem e = s->elem;
  return e;
}

bool stack_is_empty(stack s)
{
  return (s == NULL);
}

stack_elem *stack_to_array(stack s)
{
  unsigned int length = stack_size(s);
  stack_elem *array = NULL;
  if (length != 0)
  {
    array = calloc(length, sizeof(stack_elem));
  }

  if (array == NULL && length > 0)
  {
    printf("Not enouht memory \n");
    exit(EXIT_FAILURE);
  }
  for (size_t i = length - 1; i < length; i--)
  {
    array[i] = s->elem;
    s = s->next;
  }
  return array;
}

stack stack_destroy(stack s)
{
  stack p = NULL;
  while (s != NULL)
  {
    p = s;
    s = s->next;
    free(p);
  }
  return NULL;
}
