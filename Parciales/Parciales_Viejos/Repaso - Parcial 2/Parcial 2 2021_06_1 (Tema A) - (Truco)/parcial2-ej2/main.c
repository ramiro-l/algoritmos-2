#include <stdio.h>
#include <stdlib.h>

#include "truco.h"

truco_card pedir_carta()
{
    unsigned int num;
    char palo;
    printf("Ingrese un numero entre el 1 y 12 distintos de 9 y 8: \n");
    scanf("%u", &num);

    printf("Ingrese el palo de la carta  'b' -> BASTO - 'e' -> ESPADA - 'o' -> ORO  - 'c' -> COPA\n");
    scanf(" %c", &palo);

    if (num == 9 || num == 8 || num > 12)
    {
        printf("Error con el numero ingresado\n");
        exit(EXIT_FAILURE);
    }
    else if ((palo != 'e' && palo != 'b' && palo != 'o' && palo != 'c'))
    {
        printf("Error con el palo ingresado\n");
        exit(EXIT_FAILURE);
    }
    truco_card new_card = truco_card_new(num, palo);
    return new_card;
}

int main(void)
{
    truco_card a, b;
    printf("Creando la primer carta:\n");
    a = pedir_carta();
    printf("Primer carta creada correctamente!\n\n");

    printf("Creando la segunda carta:\n");
    b = pedir_carta();
    printf("Segunda carta creada correctamente!\n\n");
    if (truco_card_tie(a, b))
    {
        printf("¡La mano está parda!\n");
    }
    else
    {
        if (truco_card_win(a, b))
        {
            truco_card_dump(a);
            truco_card_dump(b);
        }
        else
        {
            truco_card_dump(b);
            truco_card_dump(a);
        }
    }

    a = truco_card_destroy(a);
    b = truco_card_destroy(b);
    return 0;
}
