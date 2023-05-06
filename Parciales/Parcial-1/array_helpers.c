/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"
static const int EXPECTED_DIM_VALUE = 2;

static const char *CITY_NAMES[CITIES] = {
    "Cordoba", "Rosario", "Posadas", "Tilcara", "Bariloche"};
static const char *SEASON_NAMES[SEASONS] = {"Low", "High"};

/**
 * @brief returns true when reach last line in products file
 * @return True when is the last line of the file, False otherwise
 */
/*static bool is_last_line(unsigned int city) {
  return city == CITIES - 1u;
}*/

void array_dump(BakeryProductTable a)
{
  for (unsigned int city = 0u; city < CITIES; ++city)
  {
    for (unsigned int season = 0u; season < SEASONS; ++season)
    {
      fprintf(stdout, "%s in season %s: Yeast (%u,%u) Butter (%u,%u) flour (%u,%u) Sales value %u",
              CITY_NAMES[city], SEASON_NAMES[season], a[city][season].yeast_cant,
              a[city][season].yeast_price, a[city][season].butter_cant,
              a[city][season].butter_price, a[city][season].flour_cant,
              a[city][season].flour_price, a[city][season].sale_value);
      fprintf(stdout, "\n");
    }
  }
}

unsigned int worst_profit(BakeryProductTable a)
{
  int min_profit, profit, cost;
  min_profit = __INT_MAX__;
  for (unsigned int city = 0; city < CITIES; city++)
  {
    for (unsigned int temp = 0; temp < SEASONS; temp++)
    {
      cost = (a[city][temp].butter_cant * a[city][temp].butter_price) + (a[city][temp].flour_cant * a[city][temp].flour_price) + (a[city][temp].yeast_cant * a[city][temp].yeast_price);

      profit = a[city][temp].sale_value - cost;

      min_profit = profit < min_profit ? profit : min_profit;
    }
  }
  /*
  En el caso que calculo el profit y el costo es mas alto que el precio del mercado,
  entonces tenermos que el profit es negativo. Algo que seria absurdo, porque perdes plata.
  Por lo tanto la funcion no contepla este caso.
  */
  return min_profit;
}

void array_from_file(BakeryProductTable array, const char *filepath)
{
  FILE *file = NULL;

  unsigned code, temporada;
  int check_cant = 0;

  file = fopen(filepath, "r");
  if (file == NULL)
  {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }
  while (!feof(file))
  {
    int res = fscanf(file, " ##%u\?\?%u ", &code, &temporada);

    // Reviso que se leyeron bien los datos y si es valido el valor de temporada y el codigo de ciudad
    if (res != EXPECTED_DIM_VALUE || temporada >= SEASONS || code >= CITIES)
    {
      fprintf(stderr, "Invalid data.\n");
      exit(EXIT_FAILURE);
    }

    BakeryProduct product = bakery_product_from_file(file);
    array[code][temporada] = product;
    check_cant = check_cant + 1;
    
  }
  if (check_cant >= (CITIES * SEASONS) + 1) // Chequeo que no se cargen mas datos de los posibles.
  {
    fprintf(stderr, "Invalid data. (mas datos de los necesarios) \n");
    exit(EXIT_FAILURE);
  }

  fclose(file);
}
