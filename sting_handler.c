#include "shell.h"

/*strlen*/
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

/*strspn*/
/**
 * _strspn - This function calculates the length of prefix
 * substring in a given string that consists only
 * of bytes from another specified string.
 *
 * @str: The string to search.
 * @accept: The prefix to be measured.
 *
 * Return: The number of bytes in 'str' which consist
 * only of bytes from 'accept'.
 */

int _strspn(char *str, char *accept)
{
	int bytes = 0;
	int i;

	while (*str)
	{
		for (i = 0; accept[i]; i++)
		{
			if (*str == accept[i])
			{
				bytes++;
				break;
			}
		}
		str++;
	}
	return (bytes);
}

/*strcat*/
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

/*strncat*/
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

/*strncmp*/
/**
 * _strncmp - This function compares one string with another.
 *
 * @str1: Pointer to the first string.
 * @str2: Pointer to the second string.
 * @n: The first n bytes of the strings to compare
 *
 * Return: Less than 0 if 'str1' is shorter than 'str2', 0 if 'str1'
 * and 'str2' match, and greater than 0 if 'str1' is longer than 'str2'
 */

int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	for (i = 0; str1[i] && str2[i] && i < n; i++)
	{
		if (str1[i] > str2[i])
			return (str1[i] - str2[i]);
		else if (str1[i] < str2[i])
			return (str1[i] - str2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
