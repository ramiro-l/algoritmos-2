#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h> /* assert() */

#define CELL_MAX ((3 * 3) - 1)

void print_sep(int length)
{
    printf("\t ");
    for (int i = 0; i < length; i++)
        printf("................");
    printf("\n");
}

void print_board(char board[3][3])
{
    int cell = 0;

    print_sep(3);
    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(3);
    }
}

char get_winner(char board[3][3])
{
    char winner = '-';
    char diaginal1 = board[0][0];
    bool ganadorDiaginal1 = true;
    // Revisa la primera diagonal
    for (size_t i = 1; i < 3; i++)
    {
        ganadorDiaginal1 = (ganadorDiaginal1 && (diaginal1 == board[i][i]));
    }
    // Si se comprueba lo anterior, sera el winer
    if (ganadorDiaginal1)
    {
        winner = diaginal1;
    }
    char diaginal2 = board[3 - 1][0];
    bool ganadorDiaginal2 = true;
    // Revisa la segunda diagonal
    for (size_t i = 0; i < 3; i++)
    {
        ganadorDiaginal2 = (ganadorDiaginal2 && (diaginal2 == board[2 - i][i]));
    }
    // Si se comprueba lo anterior, sera el winer
    if (ganadorDiaginal2)
    {
        winner = diaginal2;
    }
    bool ganadorFila;
    // Revisa todas las filas
    for (size_t i = 0; i < 3; i++)
    {
        char fila = board[i][0];
        ganadorFila = true;
        for (size_t j = 0; j < 3; j++)
        {
            ganadorFila = ganadorFila && (fila == board[i][j] && board[i][j] != '-');
        }
        // Si se comprueba lo anterior, sera el winer
        if (ganadorFila)
        {
            winner = fila;
        }
    }
    bool ganadorColumna;
    // Revisa todas las columnas
    for (size_t i = 0; i < 3; i++)
    {
        char columna = board[0][i];
        ganadorColumna = true;
        for (size_t j = 0; j < 3; j++)
        {
            ganadorColumna = (ganadorColumna && ((columna == board[j][i]) && (board[j][i] != '-')));
        }
        // Si se comprueba lo anterior, sera el winer
        if (ganadorColumna)
        {
            winner = columna;
        }
    }
    return winner;
}

bool has_free_cell(char board[3][3])
{
    bool free_cell = false;
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (board[i][j] == '-')
            {
                free_cell = true;
            }
        }
    }

    return free_cell;
}

int main(void)
{
    printf("TicTacToe [InCoMpLeTo :'(]\n");

    char board[3][3] = {
        {'-', '-', '-'},
        {'-', '-', '-'},
        {'-', '-', '-'}};

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board))
    {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0)
        {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX)
        {
            int row = cell / 3;
            int colum = cell % 3;
            if (board[row][colum] == '-')
            {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            }
            else
            {
                printf("\nCelda ocupada!\n");
            }
        }
        else
        {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-')
    {
        printf("Empate!\n");
    }
    else
    {
        printf("Ganó %c\n", winner);
    }
    return 0;
}
