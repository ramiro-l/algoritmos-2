#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 4

struct bound_data
{
  bool is_upperbound;
  bool is_lowerbound;
  bool exists;
  unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length)
{
  struct bound_data res;
  res.is_upperbound = true;
  res.is_lowerbound = true;
  res.exists = false;
  res.where = 0;
  for (size_t i = 0; i < length; i++)
  {
    if (arr[i] > value)
    {
      res.is_upperbound = false;
    }
    if (arr[i] < value)
    {
      res.is_lowerbound = false;
    }
    if (arr[i] == value)
    {
      res.exists = true;
      res.where = i;
    }
  }

  return res;
}
int main(void)
{
  int a[ARRAY_SIZE] = {0, -1, 9, 4};
  int value = 9;

  printf("Ingrese los valores del arreglo:\n");
  for (size_t i = 0; i < ARRAY_SIZE; i++)
  {
    printf("Posicion %lu :", i);
    scanf("%d", &a[i]);
  }

  printf("Ingrese un valor:\n");
  scanf("%d", &value);

  struct bound_data result = check_bound(value, a, ARRAY_SIZE);
  /*
     printf("%d", result.is_upperbound); Imprime 1
     printf("%d", result.is_lowerbound); Imprime 0
     printf("%u", result.exists);        Imprime 1
     printf("%u", result.where);
    */
  if (result.exists)
  {
    if (result.is_upperbound)
    {
      printf("El valor es maximo en la posicion %d \n", result.where);
    }
    if (result.is_lowerbound)
    {
      printf("El valor es minimo en la posicion %d \n", result.where);
    }

    if (!result.is_lowerbound && !result.is_upperbound)
    {
      printf("El valor no es maximo ni minimo pero esta en la posicion %d \n", result.where);
    }
  }
  else
  {
    if (result.is_upperbound)
    {
      printf("El valor no pertenece al arrgelo y es cota superior\n");
    }
    if (result.is_lowerbound)
    {
      printf("El valor no pertenece al arrgelo y es cota inferior\n");
    }
    if (!result.is_lowerbound && !result.is_upperbound)
    {
      printf("El valor no pertenece al arrgelo y es no cota inferior ni superior \n");
    }
  }

  return EXIT_SUCCESS;
}
