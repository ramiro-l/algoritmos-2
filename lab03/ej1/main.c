/*
  @file main.c
  @brief Main program function implementation
*/
#include <stdio.h>
#include <stdlib.h>

/** @brief structure which represent a person */
typedef struct _person
{
  int age;
  char name_initial;
} person_t;

/**
 * @brief Main program function
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(void)
{

  int x = 1;
  person_t m = {90, 'M'};
  int a[] = {0, 1, 2, 3};

  int *puntero_for_int = NULL;
  person_t *puntero_for_person = NULL;

  /*Cambio el valor de x*/
  puntero_for_int = &x;
  *puntero_for_int = 9;

  /*Cambio el valor de m.age y m.name_initial*/
  puntero_for_person = &m;
  puntero_for_person->age = 100;
  puntero_for_person->name_initial = 'F';

  /*Cambio el valor de a[0]*/
  puntero_for_int = &a[1];
  *puntero_for_int = 42;

  printf("x = %d\n", x);
  printf("m = (%d, %c)\n", m.age, m.name_initial);
  printf("a[1] = %d\n", a[1]);

  return EXIT_SUCCESS;
}
