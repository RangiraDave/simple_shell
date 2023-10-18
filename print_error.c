#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);

/**
 * error_126 - This function prints an error for "permission denied"
 * failures.
 *
 * @args: An array of strings.
 *
 * Return: An error message.
 */

char *error_126(char **args)
{
	char *err, *h_str;
	int length;

	h_str = _atoi(hist);
	if (!h_str)
		return (NULL);

	length = _strlen(name) + _strlen(h_str) + _strlen(args[0]) + 24;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(h_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, h_string);
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": Permission denied\n");

	free(h_str);
	return (err);
}

/**
 * error_127 - This function provides an  error for
 * "command not found" failure.
 *
 * @args: An array of strings.
 *
 * Return: An error message.
 */

char *error_127(char **args)
{
	char *err, *h_str;
	int length;

	h_str = _atoi(hist);
	if (!h_str)
		return (NULL);

	length = _strlen(name) + _strlen(h_str) + _strlen(args[0]) + 16;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(h_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, h_string);
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": not found\n");

	free(h_str);
	return (err);
}
