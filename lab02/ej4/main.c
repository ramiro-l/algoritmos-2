/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"

/* Maximum allowed length of the array */
static const unsigned int MAX_SIZE = 100000u;

void print_help(char *program_name)
{
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Sort an array given in a file in disk.\n"
           "\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[])
{
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2)
    {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

int main(int argc, char *argv[])
{
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];

    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);

    /* create a copy of the array */
    int copy_1[MAX_SIZE];
    array_copy(copy_1, array, length);
    int copy_2[MAX_SIZE];
    array_copy(copy_2, array, length);
    int copy_3[MAX_SIZE];
    array_copy(copy_3, array, length);

    /* reset counters and set time */
    reset_comparisons_counter();
    reset_swaps_counter();
    set_current_time();

    /* do the actual sorting */
    selection_sort(copy_1, length);

    /* show statistics for selection_sort */
    printf("statistics for selection_sort\n");
    printf("time elapsed=%g,    comparisons: %10u,    swaps: %10u\n", calculate_elapsed_time(), comparisons_number(), swaps_number());

    /* all the same for insertion_sort */

    /* reset counters and set time */
    reset_comparisons_counter();
    reset_swaps_counter();
    set_current_time();

    /* do the actual sorting */
    insertion_sort(copy_2, length);

    /* show statistics for insertion_sort */
    printf("statistics for insertion_sort\n");
    printf("time elapsed=%g,    comparisons: %10u,    swaps: %10u\n", calculate_elapsed_time(), comparisons_number(), swaps_number());

    /* all the same for quick_sort */

    /* reset counters and set time */
    reset_comparisons_counter();
    reset_swaps_counter();
    set_current_time();

    /* do the actual sorting */
    quick_sort(copy_3, length);

    /* show statistics for quick_sort */
    printf("statistics for quick_sort\n");
    printf("time elapsed=%g,    comparisons: %10u,    swaps: %10u\n", calculate_elapsed_time(), comparisons_number(), swaps_number());

    return EXIT_SUCCESS;
}

/*

./main ../input/sorted-asc-1000.in
statistics for selection_sort
time elapsed=3.097,    comparisons:     499500,    swaps:       1000
statistics for insertion_sort
time elapsed=0.024,    comparisons:       1001,    swaps:          2
statistics for quick_sort
time elapsed=5.204,    comparisons:     998134,    swaps:        997
PODEMOS VER QUE AL ESTAR TODO ORDENADO EL insertion_sort ES NUESTRA MEJOR OPCION SI EL ARREGLO ESTA ORDENADO O CASI ORDENADO


./main ../input/unsorted-1000.in
statistics for selection_sort
time elapsed=2.669,    comparisons:     499500,    swaps:       1000
statistics for insertion_sort
time elapsed=2.707,    comparisons:     252831,    swaps:     251836
statistics for quick_sort
time elapsed=0.189,    comparisons:      17761,    swaps:       2366

PODEMOS VER QUE ENTRE EL selection_sort Y insertion_sort TENEMOS POCA DIFERENCIA RELATIVA  AUNQUE ES MAS COSTOSO HACER TANTOS SWAP
POR ESO NOS CONVIENE USAR EL quick_sort QUE ES SUPER RAPIDO EN ESTE CASO


./main ../input/sorted-desc-1000.in
statistics for selection_sort
time elapsed=2.715,    comparisons:     499500,    swaps:       1000
statistics for insertion_sort
time elapsed=5.265,    comparisons:     499500,    swaps:     499500
statistics for quick_sort
time elapsed=3.745,    comparisons:     749000,    swaps:        999

PODEMOS VER QUE insertion_sort Y quick_sort SON MALOS CON EL PEOR CASO, OSEA UN ARREGLO ORDENADO PERO AL REVES
PERO NOTR QUE SI NOS CONVIENE USAR  selection_sort PORQUE TENEMOS MENOS SWAPS 

*/