////// OBS:
Para estos mensajes de error incluir la libreria:
#include <stdio.h>



//// exit(EXIT_FAILURE)
exit() es una funcion de la biblioteca estándar de C que se utiliza para terminar la ejecución de un programa de manera anormal. Se utiliza como valor de retorno para indicar que el programa ha terminado de manera anormal debido a un error.

Cuando se llama a exit(EXIT_FAILURE), el programa termina inmediatamente y se devuelve el valor de EXIT_FAILURE al sistema operativo. 

//// Ejemplos de codigos de errores:



// Verifica si malloc devolvio NULL (esto pasa cuando no hay memoria en el sistema)
    int *array = malloc(sizeof(int)*size);
    * lenght = size;

    if (size > 0 && array == NULL) {
        fprintf(stderr, "Not enough memory\n");
        exit(EXIT_FAILURE);
    }
        
        
// Verifica si se puede acceder al archivo
    
unsigned int array_from_file(const char *filepath) {
    FILE * f = NULL;
    f = fopen(filepath,"r");

    if (f == NULL)
    {
        fprintf(stderr,"No se pudo acceder al archivo %s\n",filepath);
        exit (EXIT_FAILURE);
    }
    
/*stderr es un flujo de salida de errores en la biblioteca estándar de C. Se utiliza para enviar mensajes de error y diagnóstico desde un programa hacia la salida estándar de errores.

Los mensajes enviados a stderr se muestran inmediatamente en el momento en que se producen, incluso si el programa está redirigiendo su salida estándar a otro lugar. Ayuda a distinguir claramente los mensajes de error y diagnóstico de la salida normal del programa.

Para enviar un mensaje a stderr en C, se utiliza la función fprintf() con stderr como el primer argumento como se muestra arriba.
*/
    
    
// Chequea si el formato del archivo es valido

    scanRes = fscanf(f,"%d",&elem);

    if (scanRes = EOF) 
    {
        fprintf(stderr,"Formato invalido \n");
        exit(EXIT_FAILURE);
    }
    /* fscanf devuelve EOF cuando ha alcanzado el final del archivo (error del programador) o ha ocurrido un error de lectura.*/
  
  

// Chea si se han pasado argumentos al programa mediente el archivo

char *parse_filepath(int argc, char *argv[]) {

    if (argc < 1)
    {
        fprintf(stderr,"No se han pasado suficientes argumentos al programa.\n");
        exit(EXIT_FAILURE);
    }
    
/*
argc: Es el número de argumentos que se han pasado al programa.
argv: Es un arreglo de punteros a caracteres que contiene los argumentos pasados al programa. argv[0] es el nombre del programa,
argv[1] es la ubicación del archivo y los siguientes elementos son los argumentos pasados al programa.
(Ej: lab 3 ejercicio 3)
*/ 




// Verifica que el patron sea valido

    scanRes = fscanf(file, "%u -> *%c*\n", &indexes[i], &letters[i]); 
    if (scanRes != 2)
    {
        fprintf(stderr,"Patron invalido\n");
        exit(EXIT_FAILURE);
    }
        
/* En este caso requiero que se lean dos elementos en en sus lugares (de acuerdo con el patron), si no se leen, el patron es invalido. */


static unsigned int process_FILE(FILE *file, song_t playlist[], unsigned int max_size) {
    unsigned int i = 0u;
    while (!feof(file) && i <= max_size) {
        if (i = max_size)
        {
        fprintf(stderr, "Array is too long!\n");
        exit(EXIT_FAILURE);
        }
/* Devuelve un error cuando el ciclo se sigue ejecutando debido a que el archivo no se termino pero ya se supero el max_size */
/* Notar que exit(EXIT_FAILURE); hace que salgamos del programa antes de tener una violación de segmento.*/

        unsigned int readed=0;
        process_string(file, SEPARATOR, playlist[i].song_name, MAX_NAME_LENGTH + 1u);
        process_string(file, SEPARATOR, playlist[i].artist_name, MAX_ARTIST_LENGTH + 1u);
        readed = fscanf(file, " %u  %u  ", &playlist[i].year, &playlist[i].seconds);
        if (readed != 2)
        {
        fprintf(stderr, "Invalid array.\n");
        exit(EXIT_FAILURE);
        }
/* Devuelve un error al leer del archivo una cantidad de elementos diferente a los esperados */
        ++i;
    }
    
    return (i);
}


            
            
            
            
            
            
            
            
            
            
            
            
            
