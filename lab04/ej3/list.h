#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

typedef struct _list *list;
typedef int list_elem;

/* Constructors */

list empty(void);
/*  crea una lista vacía */

list addl(list l, list_elem e);
/* agrega el elemento e al comienzo de la lista l */

/* Operations */

bool is_empty(list l);
/*Devuelve True si l es vacía*/

list_elem head(list l);
/* Devuelve el primer elemento de la lista l
   PRE: !is_empty(l)
*/

list tail(list l);
/* Elimina el primer elemento de la lista l
   PRE: !is_empty(l)
*/

list addr(list l, list_elem e);
/* Agrega el elemento e al final de la lista l*/

unsigned int length(list l);
/* Devuelve la cantidad de elementos de la lista l */

list concat(list l1, list l2);
/* Agrega al final de l todos los elementos de l1 en el mismo orden*/

list_elem index(list l, unsigned int n);
/* Devuelve el n-ésimo elemento de la lista l
   PRE:  length(l) > n
*/

list take(list l, unsigned int n);
/*  Deja en l sólo los primeros n elementos, incluido el n-ésimo y elimina el resto */

list drop(list l, unsigned int n);
/*  Elimina los primeros n elementos de l, incluido el n-ésimo */

list copy_list(list l);
/* Copia todos los elementos de l1 en una copia que la retorna */

/* Destroy */

list destroy_list(list l);
/* Libera memoria en caso que sea necesario */

#endif
