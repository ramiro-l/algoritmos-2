#ifndef WEATHER_UTILS
#define WEATHER_UTILS
#include <stdio.h>
#include "array_helpers.h"

/* Obtiene la menor temperatura mínima histórica registrada según los datos. */
int min_min_temp_hist(WeatherTable array);

/* Procedimiento que nos da la mayor temperatura máxima registrada por año según los datos. */
void max_temp_for_years(WeatherTable array, int output[YEARS]);

/* Procedimiento que nos dice el mes de la mayor cantidad mensual de precipitaciones registrada por año según los datos. */
void month_of_max_prec_for_years(WeatherTable array, unsigned int output[YEARS]);

#endif