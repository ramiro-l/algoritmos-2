#include <stdio.h>
#include "array_helpers.h"
#include "weather_utils.h"

int min_min_temp_hist(WeatherTable array)
{
    /* Inicializo y recorro todos los datos*/
    int res = array[0][0][0]._min_temp;
    for (size_t y = 0u; y < YEARS; y++)
    {
        for (size_t m = 0u; m < MONTHS; m++)
        {
            for (size_t d = 0u; d < DAYS; d++)
            {
                res = (array[y][m][d]._min_temp < res) ? array[y][m][d]._min_temp : res; // Me voy quedando siempre con el menor
            }
        }
    }
    return res;
}

void max_temp_for_years(WeatherTable array, int output[YEARS])
{
    /* Recorro todos los datos*/
    for (size_t y = 0u; y < YEARS; y++)
    {
        int max = array[y][0][0]._max_temp;
        for (size_t m = 0u; m < MONTHS; m++)
        {
            for (size_t d = 0u; d < DAYS; d++)
            {
                max = (array[y][m][d]._max_temp > max) ? array[y][m][d]._max_temp : max; // Me voy quedando siempre con el mayor de ese año
            }
        }
        output[y] = max;
    }
}

void month_of_max_prec_for_years(WeatherTable array, unsigned int output[YEARS])
{

    int month_max_prec;
    unsigned int max_prec;
    unsigned int sum_prec;
    /* Recorro todos los datos*/
    for (size_t y = 0u; y < YEARS; y++)
    {
        max_prec = 0u;
        /* Busco el mes con maxima cantidad mensual de precipitaciones de cada año*/
        for (size_t m = 0u; m < MONTHS; m++)
        {
            sum_prec = 0u;
            /* Sumo todas las precipitaciones de ese mes*/
            for (size_t d = 0u; d < DAYS; d++)
            {
                sum_prec = sum_prec + array[y][m][d]._rainfall;
            }

            if (max_prec < sum_prec) // Reviso si es la mayor de ese año
            {
                max_prec = sum_prec;
                month_max_prec = m;
            }
        }

        output[y] = month_max_prec; // Guardo el maximo
    }
}