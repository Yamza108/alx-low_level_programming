#include "main.h"
#include <stdlib.h>

/**
 * read_textfile - Reads a text file and prints to POSIX stdout
 * @filename: A pointer to filename
 * @letters: Num of letters to read and print
 * Return: if fails NULL, else actual number
 */

ssize_t read_textfile(const char *filename, size_t letters)
{
	ssize_t op, rd, wr;
	char *buffer;

	if (filename == NULL)
	{
		return (0);
	}
	buffer = malloc(sizeof(char) * letters);
	if (buffer == NULL)
		return (0);

	op = open(filename, O_RDONLY);
	rd = read(op, buffer, letters);
	wr = write(STDOUT_FILENO, buffer, rd);

	if (op == -1 || rd == -1 || wr == -1 || wr != rd)
	{
		free(buffer);
		return (0);
	}
	free(buffer);
	close(0);

	return (wr);
}
