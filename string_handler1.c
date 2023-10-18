#include "shell.h"

char *_strchr(char *str, char c);
int _strspn(char *str, char *accept);
int _strcmp(char *str1, char *str2);
int _strncmp(const char *str1, const char *str2, size_t n);

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
