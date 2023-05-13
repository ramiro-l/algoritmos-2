#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "stack.h"

struct _s_stack
{
  stack_elem elem;
  struct _s_stack *next;
  unsigned int index;
};

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
  p->index = s == NULL ? 0 : s->index + 1;

  s = p;
  return s;
}

stack stack_pop(stack s)
{
  if (!stack_is_empty(s))
  {
    stack p = s;
    s = s->next;
    free(p);
  }
  return s;
}

unsigned int stack_size(stack s)
{
  unsigned int res;
  res = s == NULL ? 0 : s->index + 1;
  return res;
}

stack_elem stack_top(stack s)
{
  assert(!stack_is_empty(s));
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
    array = malloc(sizeof(stack_elem) * length);
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

stack_elem *stack_array_destroy(stack_elem *a)
{
  free(a);
  return NULL;
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
