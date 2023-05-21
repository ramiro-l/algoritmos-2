/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "string.h" /* TAD string */

int main(void)
{
    string str_1 = string_create("Hola Mundo");
    string str_2 = string_create("Chau Mundo");

    printf("\n Es Hola Mundo < Chau Mundo : ");
    if (string_less(str_1, str_2))
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }

    printf("\n Es Chau Mundo < Hola Mundo : ");
    if (string_less(str_2, str_1))
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }

    printf("\n Es  Hola Mundo == Hola Mundo : ");
    if (string_eq(str_1, str_1))
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }

    printf("\n");

    str_1 = string_destroy(str_1);
    str_2 = string_destroy(str_2);

    return (EXIT_SUCCESS);
}
