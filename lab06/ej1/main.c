/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */

void print_help(char *program_name)
{
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
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

    return (result);
}

abb abb_from_file(const char *filepath)
{
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1)
    {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size)
    {
        abb_elem elem;
        res = fscanf(file, " %d ", &(elem));
        if (res != 1)
        {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

        ++i;
    }
    fclose(file);
    return read_tree;
}

// Función para mostrar el menú de opciones
void showOptionsMenu()
{
    printf("\n\n------------------ MENU ------------------\n");
    printf("1. Mostrar el árbol por pantalla\n");
    printf("2. Agregar un elemento\n");
    printf("3. Eliminar un elemento\n");
    printf("4. Chequear existencia de elemento\n");
    printf("5. Mostrar la longitud del árbol\n");
    printf("6. Mostrar raíz, máximo y mínimo del árbol\n");
    printf("7. Salir del programa\n\n");
}

// Funcion para inicial el menú
void openMenu(abb tree)
{

    int elem, opcion = 0;
    while (opcion != 7)
    {
        showOptionsMenu();
        printf("Ingrese una opción: ");
        fscanf(stdin, "%d", &opcion);
        printf("\n");

        if (opcion == 1)
        {
            printf("Árbol : \n");
            abb_dump(tree);
        }
        else if (opcion == 2)
        {
            printf("Ingrese el elemento a agregar: ");
            scanf("%d", &elem);
            abb_add(tree, elem);
            printf("Elemento agregado exitosamente.\n");
        }
        else if (opcion == 3)
        {
            printf("Ingrese el elemento a eliminar: ");
            scanf("%d", &elem);
            abb_remove(tree, elem);
            printf("Elemento eliminado exitosamente.\n");
        }
        else if (opcion == 4)
        {
            printf("Ingrese el elemento a verificar: ");
            scanf("%d", &elem);
            if (abb_exists(tree, elem))
            {
                printf("El elemento SI está presente en el árbol.\n");
            }
            else
            {
                printf("El elemento NO está presente en el árbol.\n");
            }
        }
        else if (opcion == 5)
        {
            printf("Longitud del árbol: %d\n", abb_length(tree));
        }
        else if (opcion == 6)
        {
            if (!abb_is_empty(tree))
            {
                printf("\n");
                printf(" La raiz: %d\n El minimo: %d\n El maximo: %d\n", abb_root(tree),
                       abb_min(tree),
                       abb_max(tree));
            }
            else
            {
                printf("\nÁrbol vacío\n");
            }
        }
        else if (opcion == 7)
        {
            printf("¡Hasta luego!\n\n");
        }
    }
}

int main(int argc, char *argv[])
{
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    /*Open menú*/
    openMenu(tree);

    /*Destroy tree*/
    tree = abb_destroy(tree);

    return (EXIT_SUCCESS);
}

/*
    c)
    Esto sucede porque la funcion esta definida de forma recursiva y
    en princio se llama a la raiz izquierda, por lo tanto intera hasta llegar a una raiz izq null
    y luego abanza a la siguiente linea y muestra el elemento (seria el minimo), luego avanza a la siguiente linea y hace
    lo mismo con la rama derecha.
    Conclucion imprime simepre el minimo del subarbol de la izquierda y  se llama recursibamente en ambas raices (izquierda y derecha).
*/
