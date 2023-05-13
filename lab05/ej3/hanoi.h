/**
 *  @file hanoi.h
 *  @brief Hanoi util functions
 *  @see https://en.wikipedia.org/wiki/Tower_of_Hanoi
 */
#ifndef __HANOI_H__
#define __HANOI_H__

typedef struct _hanoi *hanoi_t;

/**
 * @brief Initializes the towers of Hanoi
 * @param disks_count Amount of disks to insert in the source tower
 * @returns Source tower: contains 'disks_count' well-ordered disks
 *          Middle tower: empty
 *          Target tower: empty
 */
hanoi_t hanoi_init(unsigned int disks_count);

/**
 * @brief sposta tutti i dischi dalla torre di origine alla torre di destinazione
 * Seguendo i soliti vincoli di movimento (@see https://en.wikipedia.org/wiki/tower_of_hanoi)
 * Stampa anche le tre torri dopo ogni movimento
 * @note risolto usando un algoritmo ricorsivo
 */
void hanoi_solve(hanoi_t hanoi);

/**
 * @brief Prints the current state of the three towers
 */
void hanoi_print(hanoi_t hanoi);

/**
 * @brief All memory resources are freed
 */
hanoi_t hanoi_destroy(hanoi_t hanoi);

#endif
