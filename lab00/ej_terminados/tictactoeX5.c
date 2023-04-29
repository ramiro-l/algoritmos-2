#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h> /* assert() */

#define CELL_MEDIUM 5
#define CELL_MAX ((CELL_MEDIUM * CELL_MEDIUM) - 1)

void print_sep(int length)
{
    printf("\t ");
    for (int i = 0; i < length; i++)
        printf("................");
    printf("\n");
}

void print_board(char board[CELL_MEDIUM][CELL_MEDIUM])
{
    int cell = 0;

    print_sep(CELL_MEDIUM);
    for (int row = 0; row < CELL_MEDIUM; ++row)
    {
        for (int column = 0; column < CELL_MEDIUM; ++column)
        {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(CELL_MEDIUM);
    }
}

char get_winner(char board[CELL_MEDIUM][CELL_MEDIUM])
{
    char winner = '-';
    char diaginal1 = board[0][0];
    bool ganadorDiaginal1 = true;
    for (size_t i = 1; i < CELL_MEDIUM; i++)
    {
        ganadorDiaginal1 = (ganadorDiaginal1 && (diaginal1 == board[i][i]));
    }
    if (ganadorDiaginal1)
    {
        winner = diaginal1;
    }
    char diaginal2 = board[CELL_MEDIUM - 1][0];
    bool ganadorDiaginal2 = true;
    for (size_t i = 0; i < CELL_MEDIUM; i++)
    {
        ganadorDiaginal2 = (ganadorDiaginal2 && (diaginal2 == board[(CELL_MEDIUM - 1) - i][i]));
    }
    if (ganadorDiaginal2)
    {
        winner = diaginal2;
    }
    bool ganadorFila;
    for (size_t i = 0; i < CELL_MEDIUM; i++)
    {
        char fila = board[i][0];
        ganadorFila = true;
        for (size_t j = 1; j < CELL_MEDIUM; j++)
        {
            ganadorFila = (ganadorFila && (fila == board[i][j] && board[i][j] != '-'));
        }
        if (ganadorFila)
        {
            winner = fila;
        }
    }
    bool ganadorColumna;
    for (size_t i = 0; i < CELL_MEDIUM; i++)
    {
        char columna = board[0][i];
        ganadorColumna = true;
        for (size_t j = 1; j < CELL_MEDIUM; j++)
        {
            ganadorColumna = (ganadorColumna && (columna == board[j][i] && board[j][i] != '-'));
        }
        if (ganadorColumna)
        {
            winner = columna;
        }
    }

    return winner;
}

bool has_free_cell(char board[CELL_MEDIUM][CELL_MEDIUM])
{
    bool free_cell = false;
    for (size_t i = 0; i < CELL_MEDIUM; i++)
    {
        for (size_t j = 0; j < CELL_MEDIUM; j++)
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

    char board[CELL_MEDIUM][CELL_MEDIUM];
    //Inicializo el arreglo todo en vacio
    for (size_t i = 0; i < CELL_MEDIUM; i++)
    {
        for (size_t j = 0; j < CELL_MEDIUM; j++)
        {
            board[i][j] = '-';
        }
    }

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
            int row = cell / CELL_MEDIUM;
            int colum = cell % CELL_MEDIUM;
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
