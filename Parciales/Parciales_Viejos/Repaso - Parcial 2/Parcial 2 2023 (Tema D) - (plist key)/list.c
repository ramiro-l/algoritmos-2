#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "list.h"

struct _node_t
{
  unsigned int key;
  list_value value;
  struct _node_t *next;
};

typedef struct _node_t *node_t;

struct _list_t
{
  unsigned int size;
  node_t elems;
};

static bool invrep(list_t list)
{
  bool chek = true;
  unsigned int chek_size = 0;
  node_t aux = NULL;
  if (list == NULL)
  {
    chek = false;
  }
  else if (list->size == 0)
  {
    chek = list->elems == NULL;
  }
  else
  {
    aux = list->elems;
    ++chek_size;
    while (aux->next != NULL && chek)
    {
      chek = chek && aux->key < aux->next->key;
      aux = aux->next;
      ++chek_size;
    }
  }

  return chek && chek_size == list->size;
}

static struct _node_t *create_node(unsigned int key, list_value value)
{
  node_t new = malloc(sizeof(struct _node_t));
  assert(new != NULL);
  new->key = key;
  new->value = value;
  new->next = NULL;
  return new;
}

static struct _node_t *destroy_node(struct _node_t *node)
{
  assert(node != NULL);
  node->next = NULL;
  free(node);
  node = NULL;
  return node;
}

list_t list_empty(void)
{
  list_t new = malloc(sizeof(struct _list_t));
  assert(new != NULL);
  new->size = 0;
  new->elems = NULL;
  assert(invrep(new) && list_is_empty(new));
  return new;
}

list_t list_add(list_t list, unsigned int key, list_value value)
{
  assert(invrep(list));
  node_t cursor = NULL, new = NULL;
  if (list_is_empty(list) || list->elems->key > key)
  {
    new = create_node(key, value);
    new->next = list->elems;
    list->elems = new;
    ++list->size;
  }
  else if (list->elems->key == key)
  {
    list->elems->value = value;
  }
  else
  {
    cursor = list->elems;
    while (cursor->next != NULL && cursor->next->key < key)
    {
      cursor = cursor->next;
    }
    if (cursor->next != NULL && cursor->next->key == key)
    {
      cursor->next->value = value;
    }
    else if (cursor->next == NULL)
    {
      cursor->next = create_node(key, value);
      ++list->size;
    }
    else
    {
      new = create_node(key, value);
      new->next = cursor->next;
      cursor->next = new;
      ++list->size;
    }
  }
  assert(invrep(list) && !list_is_empty(list));
  return list;
}

unsigned int list_length(list_t list)
{
  assert(invrep(list));
  unsigned int res = list->size;
  assert(invrep(list));
  return res;
}

bool list_is_empty(list_t list)
{
  assert(invrep(list));
  return list->size == 0 && list->elems == NULL;
}

bool list_exists(list_t list, unsigned int key)
{
  assert(invrep(list));
  node_t cursor = list->elems;
  while (cursor != NULL && cursor->key < key)
  {
    cursor = cursor->next;
  }
  return cursor != NULL && cursor->key == key;
}

char list_search(list_t list, unsigned int key)
{
  assert(invrep(list) && list_exists(list, key));
  node_t cursor = list->elems;
  while (cursor->key < key)
  {
    cursor = cursor->next;
  }
  return cursor->value;
}

list_t list_remove(list_t list, unsigned int key)
{
  assert(invrep(list));
  node_t cursor = NULL, killme = NULL;
  if (!list_is_empty(list))
  {
    if (list->elems->key == key)
    {
      killme = list->elems;
      list->elems = list->elems->next;
      killme = destroy_node(killme);
      --list->size;
    }
    else
    {
      cursor = list->elems;
      while (cursor->next != NULL && cursor->next->key < key)
      {
        cursor = cursor->next;
      }
      if (cursor->next != NULL)
      {
        killme = cursor->next;
        cursor->next = cursor->next->next;
        killme = destroy_node(killme);
        --list->size;
      }
    }
  }

  assert(invrep(list) && !list_exists(list, key));
  return list;
}

list_t list_remove_all(list_t list)
{
  assert(invrep(list));
  while (!list_is_empty(list))
  {
    list = list_remove(list, list->elems->key);
  }
  assert(invrep(list) && list_is_empty(list));
  return list;
}

list_value *list_to_array(list_t list)
{
  assert(invrep(list));
  list_value *array = malloc(sizeof(list_value) * list->size);
  node_t cursor = list->elems;
  assert(array != NULL);
  for (size_t i = 0; i < list->size; i++)
  {
    array[i] = cursor->value;
    cursor = cursor->next;
  }
  assert(invrep(list));
  return array;
}

list_t list_destroy(list_t list)
{
  assert(invrep(list));
  list = list_remove_all(list);
  free(list);
  list = NULL;
  return list;
}
