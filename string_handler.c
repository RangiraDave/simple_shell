#include "shell.h"

int _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - This function calculates the length of a string.
 *
 * @str: A pointer to the string.
 *
 * Return: The length of the string.
 */

int _strlen(const char *str)
{
	int len = 0;

	if (!str)
		return (len);
	for (len = 0; str[len]; len++)
		;
	return (len);
}

/**
 * _strcpy - This function Copies  a string from source to destination.
 *
 * @dest: The destination location pointer.
 * @src: The source pointer.
 *
 * Return: The destination location pointer.
 */

char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - This function concatenates two strings by adding the
 * source string to the end of the destination string.
 *
 * @dest: The destination location pointer.
 * @src: The source pointer
 *
 * Return: The destination location Pointer.
 */

char *_strcat(char *dest, const char *src)
{
	char *dest_temp;
	const char *src_temp;

	dest_temp = dest;
	src_temp =  src;

	while (*dest_temp != '\0')
		dest_temp++;

	while (*src_temp != '\0')
		*dest_temp++ = *src_temp++;
	*dest_temp = '\0';
	return (dest);
}

/**
 * _strncat - This function concatenates 2 strings by adding the
 * source string to end of the destination string,
 * up to a specified number of characters.
 *
 * @dest: The destination locatin pointer.
 * @src:  The source pointer.
 * @n: Number of.
 *
 * Return: The destination location pointer.
 */

char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_length = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_length + i] = src[i];
	dest[dest_length + i] = '\0';

	return (dest);
}
