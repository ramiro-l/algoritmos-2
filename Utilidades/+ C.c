

//// Libros
https://www.amazon.com/Puzzle-Book-Alan-R-Feuer/dp/0201604612



//// memset
Requiere #include <string.h>
Es una función en el lenguaje de programación C que se utiliza para establecer el valor de un bloque de memoria con un valor específico. Su nombre significa "set memory" (establecer memoria). La función memset se encuentra en la biblioteca estándar de C, string.h.

// declaracion: 
void *memset(void *ptr, int value, size_t num);

// Parametros: 
"ptr": Puntero al bloque de memoria que se va a establecer.
"value": Valor que se utilizará para establecer el bloque de memoria. El valor se pasa como un entero, pero se convierte a un unsigned char antes de ser copiado en la memoria.
"num": Número de bytes que se establecerán en el bloque de memoria.






//// typedef
 La palabra clave typedef se usa para crear un alias de tipo llamado <nombre> para la estructura _<nombre>.
Se usa generalmente en las librerias.h






//// Cadenas 

char cadena[5];
En este ejemplo el arreglo cadena tiene capacidad para guardar un string de hasta 4 (cuatro) caracteres de
longitud. Esto es así porque toda cadena en C debe terminar con el caracter '\0'.


//// Cadenas y memoria

char *str_ptr="hola mundo!";
printf("cadena: %s\n", str_ptr);
str_ptr="hola somos campeones del mundo!";
printf("cadena: %s\n", str_ptr);


Las expresiones "hola mundo!" y "hola somos campeones del mundo!" devuelven la dirección de memoria donde el compilador guardó dicha cadena. Esta memoria se encuentra en el stack (memoria estática), por lo que no es necesario liberarla (particularmente es memoria de solo lectura por lo que si se intenta str_ptr[0]='H' va a generarse una violación de segmento).






//// size_t
size_t es un tipo de dato utilizado para representar el tamaño o la capacidad en bytes de un objeto, en particular, el tamaño de un objeto en bytes. Este tipo de dato se utiliza comúnmente en operaciones relacionadas con la memoria, como la asignación dinámica de memoria, la manipulación de matrices y la manipulación de estructuras de datos.

Generalmente se define como un tipo entero sin signo. Se garantiza que size_t es lo suficientemente grande como para representar el tamaño máximo posible de un objeto en la plataforma objetivo.

Un uso común de size_t es en la función sizeof, que devuelve el tamaño en bytes de un tipo de dato o una expresión. Por ejemplo:

size_t size = sizeof(int);
printf("El tamaño de un entero es: %zu bytes\n", size);






//// malloc y sizeof    (Espacio de memoria)

La función malloc() toma un parámetro, que es un entero sin signo de tipo size_t (muy parecido a unsigned long int) que es la cantidad de memoria en bytes que se solicita reservar. En C hay que indicar explícitamente la cantidad de bytes a reservar. El operador sizeof() devuelve la cantidad de bytes ocupados por una expresión o tipo, por lo que resulta indispensable para el uso de malloc().
Esto es muy util ademas ya que los bytes que ocupa cada tipo puede variar según la versión del sistema operativo o el microprocesador en el que se use el programa.

// Ejemplo:

p = malloc(sizeof(int));
*p = 5;
free(p);

// Heap y demas Secciones de Memoria:

Las direcciones de memoria que devuelve malloc() se encuentran en la sección de memoria denominada Heap (nada que ver con la estructura de datos que lleva el mismo nombre). 

La memoria se organiza en 4 secciones de la siguiente forma:   Código-Global-Stack-Heap.
- Código: contiene las instrucciones del programa.
- Global: contiene las variables globales.
- Stack: es donde están las variables que usamos en las funciones de nuestro programa (memoria estática). 
Se maneja de manera automática, reservando memoria para las variables declaradas en una función que se comienza a ejecutar y liberando esa memoria cuando la función termina su ejecución. 
La cantidad de memoria asignada para el Stack es limitada. Si los datos contenidos en el Stack superan dicho límite se genera un stack overflow.
Esta memoria es memoria de solo lectura por lo que si *p = "hola mundo!" y se intenta p[0]='H' va a generarse una violación de segmento.
- Heap: es la región de la memoria dinámica la cual se reserva y libera manualmente mediante malloc() y free(). 
La memoria en el Heap tiene disponible toda la memoria RAM de la computadora, por lo que mientras haya memoria libre se podrá pedir reservar nueva memoria mediante malloc(). No se debe olvidar liberar la memoria reservada cuando deje de usarse puesto que los memory leaks pueden generar a la larga que la computadora se bloquee por completo.
            
            
            
            
            
//// calloc
hace lo mismo que mallox pero inicializa en 0. 


// Ejemplo:  (asignamos un arreglo de enteros de tamaño size)
int* myArray = (int*) calloc(size, sizeof(int));


La función calloc() toma dos argumentos: el número de elementos que se desea asignar y el tamaño en bytes de cada elemento. En este caso, se desea asignar size elementos de tipo int, por lo que el tamaño en bytes de cada elemento es sizeof(int). Por lo tanto, el segundo argumento de calloc() debe ser sizeof(int).

El resultado de calloc() es un puntero a la memoria asignada. En este caso, se asigna memoria para size elementos de tipo int y se devuelve un puntero a la dirección de memoria del primer elemento. Como se utiliza un tipo de conversión de puntero (int*), el puntero devuelto por calloc() se convierte a un puntero a un entero.
            






//// realloc() 
La función realloc() en C se utiliza para cambiar el tamaño de una memoria previamente asignada dinámicamente. Permite cambiar la cantidad de memoria asignada para un bloque previamente asignado con malloc(), calloc() o realloc().

La función devuelve un puntero al bloque de memoria redimensionado. Si la función no puede asignar la memoria solicitada, devuelve NULL y el puntero original al bloque de memoria se mantiene sin cambios.

Es importante tener en cuenta que realloc() puede cambiar la ubicación del bloque de memoria. Si la función cambia la ubicación del bloque de memoria, los contenidos anteriores del bloque de memoria se copian a la nueva ubicación. Si el tamaño se reduce, los datos adicionales se descartan. Si el tamaño aumenta, los bytes adicionales se inicializan en 0.

// Sintaxis:

void *realloc(void *ptr, size_t size);

ptr: un puntero al bloque de memoria que se va a redimensionar.
size: el nuevo tamaño del bloque de memoria en bytes.




//// precedencia


struct house{
    int windows;
    int doors;
};

typedef struct house * House;

House h;
h->windows; == (*h).windows;
*h.windows por la precedencia de c es igual a *(h.windows);
*(h.windows); != (*h).windows;






    
//// division entera y division flotante
float x;
int y;
x = x / y; hece division entera
x = x / (float)y; hace division flotante 





   
