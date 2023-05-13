#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "stack.h"

int main(void)
{
  stack s;
  s = stack_empty();

  printf("-------------------------------------------------------------\n");
  printf("Agregamos el elemento 1 a la pila.\n");
  s = stack_push(s, 1);
  printf("Eliminamos el elemento de la pila.\n");
  s = stack_pop(s);
  printf("-------------------------------------------------------------\n");
  printf("La pila es vacia: ");
  if (stack_is_empty(s))
  {
    printf("True \n");
  }
  else
  {
    printf("False \n");
  }
  printf("-------------------------------------------------------------\n");
  printf("Agrege otro elemento (el 2) teniendo la pila vacia\n");
  s = stack_push(s, 2);
  printf("La pila nos queda con el primer elemento: %d\n", stack_top(s));
  printf("-------------------------------------------------------------\n");
  s = stack_pop(s);
  printf("Al llamar stack_to_array() con una pila vacia retorna NULL: ");
  if (stack_to_array(s) == NULL)
  {
    printf("True \n");
  }
  else
  {
    printf("False \n");
  }
  printf("-------------------------------------------------------------\n");
  return 0;
}