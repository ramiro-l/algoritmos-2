#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20

int main(void)
{
    char user_input[MAX_LENGTH];

    printf("Ingrese su nombre y apellido: ");
    char *res = fgets(user_input, sizeof(user_input), stdin);
    if (res == NULL)
    {
        printf("Not enouht memory \n");
        exit(EXIT_FAILURE);
    }

    user_input[strlen(user_input) - 1] = '\0'; // Eliminar el caracter \n que nos molestaba.

    printf("Te damos la bienvenida %s a este maravilloso programa!\n", user_input);

    return EXIT_SUCCESS;
}

/*
    El problema es que scanf lee solo la primera palabra, en este caso si escribimos
    NOMBRE APELLIDO, luego se va a imprimir solamente el NOMBRE.
*/
