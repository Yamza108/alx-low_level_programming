#include "main.h"

/**
 * print_binary - print a bin rep of a num
 * @n: the number to be printed in bin
 */

void print_binary(unsigned long int n)
{
	if (n > 1)
		print_binary(n >> 1);
	_putchar((n & 1) + '0');
}
