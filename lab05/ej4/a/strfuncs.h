#ifndef __STRFUNCS_H__
#define __STRFUNCS_H__

#include <stdlib.h>
/*
Calcula la longitud de la cadena apuntada por str.
*/
size_t string_length(const char *str);

/*
Retorna una nueva cadena que se obtiene tomando los
caracteres de str que son distintos del caracter c.
*/
char *string_filter(const char *str, char c);

#endif
