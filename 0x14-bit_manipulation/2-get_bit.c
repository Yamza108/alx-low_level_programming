#include "main.h"

/**
 * get_bit - gets value of a bit at random index
 * @n: bit
 * @index: index to get value from, from 0
 * Return: bit value otherwise -1.
 */

int get_bit(unsigned long int n, unsigned int index)
{
	if (index >= (sizeof(unsigned long int) * 8))
		return (-1);
	if ((n & (1 << index)) == 0)
		return (0);
	return (1);
}
