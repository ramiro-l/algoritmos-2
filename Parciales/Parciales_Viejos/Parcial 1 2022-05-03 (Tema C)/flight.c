/*
  @file layover.c
  @brief Implements flight structure and methods
*/
#include <stdlib.h>
#include "flight.h"

static const int AMOUNT_OF_FLIGHT_VARS = 2;

Flight flight_from_file(FILE *file, char code, unsigned int arrival_hour)
{
  unsigned int aux_type;
  Flight flight;
  flight.code = code;
  flight.hour = arrival_hour;

  int res = fscanf(file, " %u %u ", &aux_type, &flight.items_amount);
  if (res != AMOUNT_OF_FLIGHT_VARS)
  {
    fprintf(stderr, "Invalid file.\n");
    exit(EXIT_FAILURE);
  }
  if (aux_type != 0 && aux_type != 1)
  {
    fprintf(stderr, "Invalid file.\n");
    exit(EXIT_FAILURE);
  }
  flight.type = aux_type == 0 ? boxes : letters;

  return flight;
}
