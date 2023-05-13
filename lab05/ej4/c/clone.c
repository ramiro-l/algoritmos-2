#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *string_clone(const char *str, size_t length)
{
    char *clone = malloc((length * sizeof(char)) + sizeof(char));
    if (clone == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < length; i++)
    {
        clone[i] = str[i];
    }
    clone[length] = '\0';
    return clone;
}

size_t string_length(const char *str)
{
    size_t length = 0;
    while (str[length] != '\0')
    {
        length++;
    }
    return length;
}

int main(void)
{
    char *original = ""
                     "______ time ago in a galaxy far, far away...\n\n\n"
                     "         _______..___________.     ___      .______             \n"
                     "        /       ||           |    /   \\     |   _  \\          \n"
                     "       |   (----``---|  |----`   /  ^  \\    |  |_)  |          \n"
                     "        \\   \\        |  |       /  /_\\  \\   |      /        \n"
                     "    .----)   |       |  |      /  _____  \\  |  |\\  \\----.    \n"
                     "    |_______/        |__|     /__/     \\__\\ | _| `._____|     \n"
                     "                                                                \n"
                     "____    __    ____      ___      .______           _______.     \n"
                     "\\   \\  /  \\  /   /     /   \\     |   _  \\         /       |\n"
                     " \\   \\/    \\/   /     /  ^  \\    |  |_)  |       |   (----` \n"
                     "  \\            /     /  /_\\  \\   |      /         \\   \\    \n"
                     "   \\    /\\    /     /  _____  \\  |  |\\  \\----..----)   |   \n"
                     "    \\__/  \\__/     /__/     \\__\\ | _| `._____||_______/     \n"
                     "\n\n\n"
                     "                     Episode IV \n\n"
                     "                     A NEW HOPE \n\n"
                     "                     It is a period of civil war. Rebel\n"
                     "spaceships, striking from a hidden base, have won their\n"
                     "first victory against the evil Galactic Empire. During the\n"
                     "battle, Rebel spies managed to steal secret plans to the\n"
                     "Empire’s ultimate weapon, the DEATH STAR, an armored space\n"
                     "station with enough power to destroy an entire planet.\n"
                     "Pursued by the Empire’s sinister agents, Princess Leia\n"
                     "races home aboard her starship, custodian of the stolen\n"
                     "plans that can save her people and restore freedom to the\n"
                     "galaxy...\n";
    char *copy = NULL;

    copy = string_clone(original, string_length(original) + 1);
    copy[0] = 'A';
    copy[1] = ' ';
    copy[2] = 'l';
    copy[3] = 'o';
    copy[4] = 'n';
    copy[5] = 'g';
    printf("Copia   : %s\n", copy);
    free(copy);
    return EXIT_SUCCESS;
}

/*
    Tenia un problema al calcular el lenght ya que sizeof(original) retorna el tamaño del puntero char* y
    no el tamaño de la cadena de caracteres a la que apunta. Lo solucionamos calculandolo con un while.

    El principal problema estaba en la funcion de string_clone, porque teniamos una varible llamada copy,
    en la cual le asiganabamos el string pero al terminar la funcion string_clone esta variable y su contenido
    son eliminados porque estan en una variable local. Por esta razon,  ahora se reseva espacio en memoria dinamica,
    se copia el contenido y luego se pasa el puntero.




    ??????????????????????????????????????????????????????????????????????????????????????????????????????????????
*/