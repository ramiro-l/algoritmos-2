#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s)
{
    unsigned int i = 0;
    while (s[i] != '\0' && i < FIXSTRING_MAX) // Itero hasta encontrar un \0 o alcanzar la cantidad maxima de caracteres
    {
        i++;
    }

    return i;
}

bool fstring_eq(fixstring s1, fixstring s2)
{
    bool res = true;
    unsigned int length_s1 = fstring_length(s1); // Obtenemos el tamaño de s1.
    unsigned int length_s2 = fstring_length(s2); // Obtenemos el tamaño de s1.

    if (length_s1 == length_s2) // Reviso que los tamaños coincidan sino no es posible.
    {
        for (unsigned int i = 0; i < length_s1; i++)
        {
            res = res && (s1[i] == s2[i]); // Revisa que sean iguales los elementos en la posicion i.
        }
    }
    else
    {
        res = false;
    }
    return res;
}

bool fstring_less_eq(fixstring s1, fixstring s2)
{
    bool res = true;

    unsigned int length_s1 = fstring_length(s1); // Obtenemos el tamaño de s1.
    unsigned int length_s2 = fstring_length(s2); // Obtenemos el tamaño de s1.

    unsigned int i = 0;

    while ((i < length_s1) && (i < length_s2) && res) // En el caso que una cadena termine no hay que comprarar mas
    {
        if (s1[i] < s2[i])
        { // Si es menor la letra, terminar el while
            res = true;
            i = length_s1;
        }
        if (s1[i] == s2[i]) // Si es igual la letra, pasar a la siguiente letra para seguir revisando
        {
            i++;
        }
        if (s1[i] > s2[i])
        { // Si la letra es mayor, terminar el while
            res = false;
            i = length_s1;
        }
    }
    return res;
}

void fstring_set(fixstring s1, const fixstring s2)
{
    int i = 0;
    while (i < FIXSTRING_MAX && s2[i] != '\0')
    {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
}

void fstring_swap(fixstring s1, fixstring s2)
{
    fixstring aux;
    fstring_set(aux, s1); // Asigno al auxiliar s1
    fstring_set(s1, s2);  // Asigno a s1 el valor de s2
    fstring_set(s2, aux); // Asigno a s2 el valor de aux = s1
}
