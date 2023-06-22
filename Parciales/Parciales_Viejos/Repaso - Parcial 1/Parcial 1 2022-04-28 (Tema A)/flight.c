/*
  @file layover.c
  @brief Implements flight structure and methods
*/
#include <stdlib.h>
#include "flight.h"

static const int AMOUNT_OF_FLIGHT_VARS = 3;

Flight flight_from_file(FILE *file, char code)
{
  Flight flight;
  unsigned int type_aux;
  flight.code = code;
  int res = fscanf(file, EXPECTED_FLIGHT_FILE_FORMAT, &type_aux, &flight.hour, &flight.passengers_amount);

  if (res != AMOUNT_OF_FLIGHT_VARS)
  {
    fprintf(stderr, "Invalid file.\n");
    exit(EXIT_FAILURE);
  }
  else if ((type_aux != 0u && type_aux != 1u) || (flight.hour > 24u && flight.hour != 0u))
  {
    fprintf(stderr, "Invalid format.\n");
    exit(EXIT_FAILURE);
  }

  flight.type = type_aux == 0 ? arrival : departure;

  return flight;
}
