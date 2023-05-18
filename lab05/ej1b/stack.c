#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "stack.h"

struct _s_stack
{
  struct stack_node *fst;
  unsigned int size;
};

struct stack_node
{
  stack_elem elem;
  struct stack_node *next;
};

bool inv_rep(stack s)
{
  struct stack_node *aux = NULL;
  bool b = (s != NULL);
  if (b)
  {
    aux = s->fst;
    for (size_t i = 0; i < s->size; i++)
    {
      aux = aux->next;
    }
    b = (aux == NULL);
  }

  return b;
}

stack stack_empty()
{
  stack p = malloc(sizeof(struct _s_stack));
  p->size = 0;
  p->fst = NULL;
  return p;
}

stack stack_push(stack s, stack_elem e)
{
  assert(inv_rep(s));
  struct stack_node *p = NULL;
  p = malloc(sizeof(struct stack_node));
  if (p == NULL)
  {
    printf("Not enouht memory \n");
    exit(EXIT_FAILURE);
  }

  p->elem = e;
  p->next = s->fst;
  s->size = s->size + 1;

  s->fst = p;
  return s;
}

stack stack_pop(stack s)
{
  assert(inv_rep(s));
  assert(!stack_is_empty(s));
  struct stack_node *p = s->fst;
  s->fst = (s->fst)->next;
  s->size = s->size - 1;
  free(p);
  return s;
}

unsigned int stack_size(stack s)
{
  assert(inv_rep(s));
  return s->size;
}

stack_elem stack_top(stack s)
{
  assert(inv_rep(s));
  return (s->fst)->elem;
}

bool stack_is_empty(stack s)
{
  assert(inv_rep(s));
  return (s->size == 0 && s->fst == NULL);
}

stack_elem *stack_to_array(stack s)
{
  assert(inv_rep(s));
  unsigned int length = stack_size(s);
  struct stack_node *p = NULL;
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
  p = s->fst;
  for (size_t i = length - 1; i < length; i--)
  {
    array[i] = p->elem;
    p = p->next;
  }
  return array;
}

stack stack_destroy(stack s)
{
  assert(inv_rep(s));
  struct stack_node *p = NULL;
  struct stack_node *q = s->fst;
  while (q != NULL)
  {
    p = q;
    q = p->next;
    free(p);
    p = NULL;
  }
  free(s);
  return NULL;
}
