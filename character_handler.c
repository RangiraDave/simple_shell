#include "shell.h"

/*strchr*/
/**
 * _strchr - This function  ocates a character in a string.
 *
 * @str: The string to go through.
 * @c: The character to be located.
 *
 * Return: If 'c' is found, it returns a pointer to the first occurence
 * and if not found, it returns NULL.
 */

char *_strchr(char *str, char c)
{
	int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == c)
			return (str + i);
	}

	return (NULL);
}

/*strcmp*/
/**
 * _strcmp - This function compares two strings.
 *
 * @str1: The first string to be compared.
 * @str2: The second string to be compared.
 *
 * Return: A positive byte difference, if 'str1' is greater than 'str2'.
 * 0 if 'str1' is equal to 'str2' and a negative byte
 * difference if 'str1' is less than 'str2'.
 */

int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	if (*str1 != *str2)
		return (*str1 - *str2);

	return (0);
}

/*strcpy*/
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

	if (!src)
		return (NULL);
	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
