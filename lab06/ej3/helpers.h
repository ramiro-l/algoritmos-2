#ifndef _HELPERS_H
#define _HELPERS_H

#include <stdio.h>
#include "string.h"

string readstring_from_stdin(void);
/*
 * A wrapper for readline_from_stdin that uses standard string library.
 * Un contenedor para Readline_from_stdin que usa la biblioteca de cadenas estándar.
 */

char *readline_from_stdin(void);
/*
 * Read the user input from standard input until a newline is detected,
 * and return the corresponding (dinamically allocated) string.
 *
 * The caller to this function is responsible for the allocated memory.
 *
 * POST: A new null-terminated string is returned with the content read from
 * standard input, or NULL if there was an error.
 *
 * Lea la entrada del usuario de la entrada estándar hasta que se detecte una nueva línea,
 * y devuelve la cadena correspondiente (asignada dinámica).
 *
 * La persona que llama a esta función es responsable de la memoria asignada.
 *
 * POST: se devuelve una nueva cadena nula con el contenido leído desde
 * Entrada estándar, o nula si hubo un error.
 */

char *readline(FILE *file);
/*
 * Read the user input from specified FILE * until a newline is detected,
 * and return the corresponding (dinamically allocated) string.
 *
 * The caller to this function is responsible for the allocated memory.
 *
 * POST: A new null-terminated string is returned with the content read,
 * or NULL if there was an error.
 *
 *
 * Lea la entrada del usuario del archivo especificado * hasta que se detecte una nueva línea,
 * y devuelve la cadena correspondiente (asignada dinámica).
 *
 * La persona que llama a esta función es responsable de la memoria asignada.
 *
 * Publicación: se devuelve una nueva cadena nula con el contenido leído,
 * o nulo si hubo un error.
 */

#endif
