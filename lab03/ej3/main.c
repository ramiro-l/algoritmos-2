#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length)
{
    printf("\"");
    for (unsigned int j = 0u; j < length; j++)
    {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

char *parse_filepath(int argc, char *argv[])
{
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count)
    {
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

unsigned int read_file_write_arrays(char *filepath, unsigned int indexes[], char letters[])
{
    unsigned int length = 0u;
    unsigned int check_length = 0u;
    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        printf("Error al cargar el archivo.\n");
        exit(EXIT_FAILURE);
    }
    while ((!feof(file)) && length < MAX_SIZE) // Ejecutar el bulce hasta que termine el archivo
    {
        /* Guarda los valores respetando el formato y aumenta el length si esta todo bien */
        if (2 != fscanf(file, " %u -> *%c* ", &indexes[length], &letters[length]))
        {
            fprintf(stderr, "Error reading the file.\n");
            exit(EXIT_FAILURE);
        }
        check_length = check_length + indexes[length];
        ++length;
    }

    fclose(file);

    /* Reviso que todos los indices esten bien. */
    /* Como se hace, transforme la formula de gauss para no tener que hacer la divicion y tener problemas con la divicion entera
        y luego compraro que coincidan los valores recopilados en el archivo con el indice calculado. */
    if (length == 0u)
    {
        printf("Error the array is empty \n");
        exit(EXIT_FAILURE);
    }
    if (check_length * 2u != ((length - 1u) * length))
    {
        printf("Error with file indexes \n");
        exit(EXIT_FAILURE);
    }

    return length;
}

static void sort_array(unsigned int indexes[], char letters[], char sorted[], unsigned int length)
{
    unsigned int pos_aux;
    char letter_aux;
    for (size_t i = 0u; i < length; i++)
    {
        /*Recuperamos ambos valores que estaban asignados <in> y  el <char>*/
        pos_aux = indexes[i];
        letter_aux = letters[i];

        /* Al tener la psocicion donde debe estar, accedemos y le asignamos el valor correspondiente*/
        sorted[pos_aux] = letter_aux;
    }
}

int main(int argc, char *argv[])
{
    char *filepath = NULL;
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length;

    filepath = parse_filepath(argc, argv);

    length = read_file_write_arrays(filepath, indexes, letters);

    sort_array(indexes, letters, sorted, length);

    dump(sorted, length);

    return EXIT_SUCCESS;
}
