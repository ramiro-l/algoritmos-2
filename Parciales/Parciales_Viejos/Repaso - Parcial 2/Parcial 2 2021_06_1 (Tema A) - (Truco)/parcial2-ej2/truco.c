#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "truco.h"

struct _s_truco_card
{
    unsigned int num;
    unsigned int rango;
    char palo;
};

#define ESPADA "ESPADA"
#define BASTO "BASTO"
#define ORO "ORO"
#define COPA "COPA"

static const char *suit_str(char p)
{
    const char *str;
    if (p == 'e')
    {
        str = ESPADA;
    }
    else if (p == 'b')
    {
        str = BASTO;
    }
    else if (p == 'o')
    {
        str = ORO;
    }
    else if (p == 'c')
    {
        str = COPA;
    }
    return str;
}

static void dump(int num, char suit)
{
    printf(" ----------------\n"
           " : %2d           :\n"
           " :              :\n"
           " :              :\n"
           " :    "
           "%-7s"
           "   :\n"
           " :              :\n"
           " :              :\n"
           " :              :\n"
           " :           %2d :\n"
           " ----------------\n",
           num, suit_str(suit), num);
}

static int card_rank(int num, char suit)
{
    int rank = 0;

    if (4 <= num && num <= 12)
    {
        if (num == 9 || num == 8)
        {
            printf("Error: el numero de carta (9 o 8) no exitse.");
        }
        else if (num == 12)
        {
            rank = 8;
        }
        else if (num == 11)
        {
            rank = 7;
        }
        else if (num == 10)
        {
            rank = 6;
        }
        else if (num == 7)
        {
            rank = 3;
        }
        else if (num == 6)
        {
            rank = 2;
        }
        else if (num == 5)
        {
            rank = 1;
        }
        else
        {
            rank = 0;
        }
    }
    else
    {
        if (num == 1)
        {
            rank = 9;
        }
        else if (num == 2)
        {
            rank = 10;
        }
        else
        {
            rank = 11;
        }
    }

    if (num == 1 && suit == 'e')
    {
        rank = 15;
    }
    else if (num == 1 && suit == 'b')
    {
        rank = 14;
    }
    else if (num == 7 && suit == 'e')
    {
        rank = 13;
    }
    else if (num == 7 && suit == 'o')
    {
        rank = 12;
    }
    return rank;
}

static bool invrep(truco_card c)
{
    bool valid_card = true;
    valid_card = c->num != 9 && c->num != 8 && c->num <= 12;
    valid_card = valid_card && (c->palo == 'e' || c->palo == 'b' || c->palo == 'o' || c->palo == 'c');
    valid_card = valid_card && (c->rango <= 15 && c->rango != 5 && c->rango != 4);
    return valid_card;
}

truco_card truco_card_new(int num, char p)
{
    truco_card card = malloc(sizeof(struct _s_truco_card));
    assert(card != NULL);
    card->num = num;
    card->palo = p;
    card->rango = card_rank(num, p);
    assert(invrep(card));
    return card;
}

bool truco_card_win(truco_card a, truco_card b)
{
    assert(invrep(a) && invrep(b));
    bool card_a_win = a->rango > b->rango;
    return card_a_win;
}

bool truco_card_tie(truco_card a, truco_card b)
{
    assert(invrep(a) && invrep(b));
    bool is_a_tie = a->rango == b->rango;
    return is_a_tie;
}

void truco_card_dump(truco_card c)
{
    assert(invrep(c));
    dump(c->num, c->palo);
}

truco_card truco_card_destroy(truco_card c)
{
    assert(invrep(c));
    free(c);
    c = NULL;
    return c;
}
