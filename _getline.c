#include "shell.h"

void *_realloc(void *ptr, unsigned int old_sz, unsigned int new_sz);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *channel);

/**
 * _realloc - This function reallocates memory.
 *
 * @ptr: A pointer to the memory block to be reallocated.
 * @old_sz: The size of the old memmory block.
 * @new_sz: The new size of the memory block.
 *
 * Return: The size of the memory block.
 */

void *_realloc(void *ptr, unsigned int old_sz, unsigned int new_sz)
{
	void *m;
	char *pointer_cpying, *pad;
	unsigned int in;

	if (new_sz == old_sz)
		return (ptr);

	if (ptr == NULL)
	{
		m = malloc(new_sz);
		if (m == NULL)
			return (NULL);

		return (m);
	}

	if (new_sz == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	pointer_cpying = ptr;
	m = malloc(sizeof(*pointer_cpying) * new_sz);
	if (m == NULL)
	{
		free(ptr);
		return (NULL);
	}

	pad = m;

	for (in = 0; in < old_sz && in < new_sz; in++)
		pad[in] = *pointer_cpying++;

	free(ptr);
	return (m);
}

/**
 * assign_lineptr - This function updates the line pointer variable for
 * the _getline function.
 *
 * @lineptr: A pointer  for storing strings
 * @n: A pointer
 * @buffer: A string
 * @x: A buffer size
 */

void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t x)
{
	if (*lineptr == NULL)
	{
		if (x > 120)
			*n = x;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < x)
	{
		if (x > 120)
			*n = x;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - This function reads input from a channel.
 *
 * @lineptr: Input buffer.
 * @n: Line pointer.
 * @channel: Read way
 *
 * Return: The number of bytes read
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *channel)
{
	static ssize_t inp;
	ssize_t re;
	char c = 'y', *buff;
	int x;

	if (inp == 0)
		fflush(channel);
	else
		return (-1);
	inp = 0;

	buff = malloc(sizeof(char) * 120);
	if (!buff)
		return (-1);

	while (c != '\n')
	{
		x = read(STDIN_FILENO, &c, 1);
		if (x == -1 || (x == 0 && inp == 0))
		{
			free(buff);
			return (-1);
		}
		if (x == 0 && inp != 0)
		{
			inp++;
			break;
		}

		if (inp >= 120)
			buff = _realloc(buff, inp, inp + 1);

		buff[inp] = c;
		inp++;
	}
	buff[inp] = '\0';

	assign_lineptr(lineptr, n, buff, inp);

	re = inp;
	if (x != 0)
		inp = 0;
	return (re);
}
