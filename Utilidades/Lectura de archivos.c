



//// fopen() 

fopen se utiliza para abrir un archivo y crear un puntero de archivo que se utilizará para acceder al archivo. 
La función devuelve un puntero de tipo FILE que se utilizará para acceder al archivo abierto.

// Sintaxis:
FILE *fopen(const char *filename, const char *mode);

filename: nombre del archivo que se va a abrir

mode: cadena que especifica el modo en el que se va a abrir el archivo.

"r" abre el archivo para lectura. Si el archivo no existe, la función devuelve un puntero nulo.
"w" abre el archivo para escritura. Si el archivo ya existe, su contenido se borra. Si el archivo no existe, se crea uno nuevo.
"a" abre el archivo para añadir información al final del archivo. Si el archivo no existe, se crea uno nuevo.
"r+" abre el archivo para leer y escribir. El archivo debe existir previamente.
"w+" abre el archivo para leer y escribir. Si el archivo ya existe, su contenido se borra. Si el archivo no existe, se crea uno nuevo.
"a+" abre el archivo para añadir información al final del archivo y para lectura. Si el archivo no existe, se crea uno nuevo.





//// feof()
feof() es una función en la biblioteca estándar de C que se utiliza para determinar si se ha alcanzado el final de un archivo. La función toma como argumento un puntero al archivo que se está leyendo ( Ej: FILE *fp = fopen("datos.txt", "r"); ) y devuelve un valor entero. Si el valor devuelto es distinto de cero, significa que se ha alcanzado el final del archivo.

// Ejemplo:

while (!feof(file)) { ... }

/*0 = false*/






//// fprintf()
fprintf() es una función de la biblioteca estándar de C que se utiliza para imprimir datos en un archivo o en la salida estándar. Su nombre es una abreviatura de "formatted print" (impresión con formato), lo que significa que permite imprimir datos en un formato específico.


// Sintaxis:

int fprintf(FILE *stream, const char *format, ...);
stream: puntero al archivo en el que se imprimirán los datos. Puede ser un puntero al archivo de salida estándar stdout, al archivo de salida de errores stderr, o a un archivo especificado por el usuario utilizando la función fopen().

format: cadena de caracteres que especifica el formato en el que se imprimirán los datos.

...: datos que se imprimirán, en función del formato especificado. Estos datos pueden ser variables de cualquier tipo, como enteros, flotantes, cadenas de caracteres, etc.

La función fprintf() es similar a la función printf(), que se utiliza para imprimir datos en la salida estándar stdout. La diferencia es que fprintf() permite especificar un archivo diferente de la salida estándar.


/*stdout es un flujo de salida estándar en la biblioteca estándar de C. Se utiliza para enviar mensajes y datos desde un programa hacia la salida estándar.

La salida estándar se envía a la consola o a la pantalla, lo que significa que los mensajes enviados a stdout se muestran directamente en la pantalla en el momento en que se producen.

Para enviar un mensaje a stdout en C, se utiliza la función printf().*/

//Ejemplo:

#include <stdio.h>

int main() {
    FILE *fp;
    fp = fopen("datos.txt", "w");
    if (fp == NULL) {
        fprintf(stderr,"No se pudo abrir el archivo.\n");
        return 1;
    }
    fprintf(fp, "El valor de pi es aproximadamente %f.\n", 3.14159);
    fclose(fp);
    return 0;
}
Este código abre el archivo "datos.txt" en modo de escritura, utiliza fprintf() para imprimir un mensaje en el archivo, y luego cierra el archivo. El mensaje impreso en el archivo será "El valor de pi es aproximadamente 3.141590."
Si "datos.txt" no es accesible, entonces enviara con fprintf un mensaje de error al archivo de salida de errores stderr que mostrara inmediatamente el mensaje de error.






//// fgetc()
fgetc() es una función en el lenguaje de programación C que lee un solo carácter desde un flujo de archivo. Está definida en el archivo de encabezado stdio.h y toma un puntero a archivo como argumento. La función lee el siguiente carácter desde el archivo asociado con el puntero a archivo y lo devuelve como un entero. Si no hay más caracteres para leer, la función devuelve el valor especial EOF (que significa "Fin De Archivo" en español).




//// fgets()
La función fgets() se utiliza para leer una línea de texto desde un archivo o desde la entrada estándar (como el teclado) y almacenarla en un arreglo de caracteres (char). 

// Sintaxis:

char* fgets(char* cadena, int longitud, FILE* archivo);

// Parametros:

"cadena": Es un puntero a un arreglo de caracteres donde se almacenará la línea de texto leída.
"longitud": Es un entero que especifica la longitud máxima de caracteres que se pueden leer, incluyendo el carácter de nueva línea ('\n') y el carácter nulo ('\0') final. ej: sizeof(...)
"archivo": Es un puntero al archivo desde el cual se leerá la línea de texto. Puede ser stdin para leer desde la entrada estándar (teclado) o un puntero a un archivo abierto en modo lectura.

La función fgets() lee caracteres de archivo hasta alcanzar longitud - 1 caracteres, o hasta encontrar un carácter de nueva línea ('\n'), o hasta llegar al final del archivo. Luego, almacena los caracteres leídos en cadena y agrega el carácter nulo ('\0') final al final de la cadena.



//// fscanf()
Lee datos de un archivo de texto o de un flujo de entrada estándar (stdin), de la misma manera que scanf lee datos desde la entrada estándar. 

/* stdin es una abreviatura de "standard input" (entrada estándar) y es un flujo de entrada estándar en los sistemas operativos Unix y otros sistemas que siguen el estándar POSIX.

En el lenguaje de programación C, stdin es una macro que representa el flujo de entrada estándar y se utiliza para leer datos desde la entrada estándar del sistema, que generalmente es el teclado. stdin es un puntero a un objeto de tipo FILE, que se define en la biblioteca estándar de C y se utiliza para leer y escribir archivos. */

// Sintaxis:
int fscanf(FILE *archivo, const char *formato, ...);

archivo: puntero al archivo que se desea leer.

formato: es una cadena de caracteres que especifica el formato de los datos que se van a leer.
    "%d": Lee un número entero con signo en formato decimal.
    "%f": Lee un número en formato de coma flotante.
    "%lf": Lee un número en formato de coma flotante de doble precisión.
    "%c": Lee un carácter.
    "%s": Lee una cadena de caracteres.
    "%u": Lee un número entero sin signo en formato decimal.
    "%x": Lee un número entero sin signo en formato hexadecimal.
    "%o": Lee un número entero sin signo en formato octal.

Los argumentos son las direcciones en las que se almacenarán los datos leídos.

//Ejemplo:

datos.txt = 20, 30
#include <stdio.h>

int main() {
    FILE *archivo = fopen("datos.txt", "r");
    int a, b;
    fscanf(archivo, "%d, %d", &a, &b);
    printf("a = %d, b = %d\n", a, b);
    fclose(archivo);
    return 0;
}

//Tips:

fscanf(archivo, "%d, %d \n", &a, &b);
/*tener en cuenta los saltos de linea para los patrones*/

fscanf(archivo, "%d, %d \?\n", &a, &b);
/*? no es un signo de pregunta ya que se usa en c para otras cosas, \? en cambio si es un signo de pregunta*/

//// fclose()

fclose se utiliza para cerrar un archivo abierto con fopen.

Es importante cerrar correctamente los archivos que se abren con fopen utilizando fclose, ya que esto libera los recursos de sistema utilizados por el archivo y asegura que los datos se guarden en el archivo correctamente. Si no se cierra un archivo, es posible que los datos no se guarden correctamente y que se produzcan errores de lectura y escritura en futuras operaciones con el archivo.

La función devuelve un valor entero que indica si se ha cerrado correctamente el archivo (0 si se ha cerrado correctamente, y un valor distinto de 0 si ha habido un error).

//Sintaxis:

int fclose(FILE *stream);

stream: es el puntero de archivo que se va a cerrar. 




//// Para evitar la duplicacion de codigo:

La directiva de preprocesador #ifndef se utiliza para evitar que se incluya una sección de código varias veces en un archivo de programa. La directiva #ifndef significa "if not defined" (si no está definido) y se utiliza en conjunto con la directiva #define para crear macros de preprocesador que eviten la duplicación de código.

//Sintaxis:

#ifndef NOMBRE_MACRO
#define NOMBRE_MACRO

<código que se incluye sólo si NOMBRE_MACRO no está definido>

#endif


En esta estructura, el NOMBRE_MACRO es el nombre de la macro que se está definiendo. Si la macro ya está definida, entonces el código dentro del #ifndef y #endif no se incluirá en el programa final. Si la macro no está definida, entonces el código dentro del #ifndef y #endif se incluirá en el programa final.

En resumen, #ifndef se utiliza para evitar la inclusión múltiple de un mismo archivo de encabezado o sección de código en un programa, lo que puede generar errores de compilación y desperdiciar recursos de la computadora.



