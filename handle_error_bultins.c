#include "shell.h"

char *env_error(char **args);
char *alias_error(char **args);
char *exit_error(char **args);
char *cd_error(char **args);
char *syntax_error(char **args);

/**
 * env_error - This function displays an error message
 * related to shell_environment.
 *
 * @args: An array of arguments.
 *
 * Return: The error msg
 */

char *env_error(char **args)
{
	char *err, *h_str;
	int length;

	h_str = _atoi(hist);
	if (!h_str)
		return (NULL);

	args--;
	length = _strlen(name) + _strlen(h_str) + _strlen(args[0]) + 45;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(h_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, h_str);
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": Failed to add or remove from the environment\n");

	free(h_str);
	return (err);
}

/**
 * alias_error - This function displays an error message
 * related to shell alias handling
 *
 * @args: An array of arguments
 *
 * Return: The error msg
 */

char *alias_error(char **args)
{
	char *err;
	int length;

	length = _strlen(name) + _strlen(args[0]) + 13;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
		return (NULL);

	_strcpy(err, "alias: ");
	_strcat(err, args[0]);
	_strcat(err, " Command not found\n");

	return (err);
}

/**
 * exit_error - This function displays an  error message
 *  related to shell_exit.
 *
 * @args: An array of arguments
 *
 * Return: The error msg.
 */

char *exit_error(char **args)
{
	char *err, *h_str;
	int length;

	h_str = _atoi(hist);
	if (!h_str)
		return (NULL);

	length = _strlen(name) + _strlen(h_str) + _strlen(args[0]) + 27;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(h_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, h_str);
	_strcat(err, ": exit: Illegal number: ");
	_strcat(err, args[0]);
	_strcat(err, "\n");

	free(h_str);
	return (err);
}

/**
 * cd_error - This function displays  an error message
 * related to changing directories in the shell.
 *
 * @args: An array of arguments
 *
 * Return: The error msg.
 */

char *cd_error(char **args)
{
	char *err, *h_str;
	int length;

	h_str = _atoi(hist);
	if (!h_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	length = _strlen(name) + _strlen(h_str) + _strlen(args[0]) + 24;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(h_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, h_str);
	if (args[0][0] == '-')
		_strcat(err, ": cd: No directory found");
	else
		_strcat(err, ": cd: can not cd to ");
	_strcat(err, args[0]);
	_strcat(err, "\n");

	free(h_str);
	return (err);
}

/**
 * syntax_error - This function displays  an error message for syntax errors.
 *
 * @args: An array of arguments
 *
 * Return: The error msg.
 */

char *syntax_error(char **args)
{
	char *err, *h_str;
	int length;

	h_str = _atoi(hist);
	if (!h_str)
		return (NULL);

	length = _strlen(name) + _strlen(h_str) + _strlen(args[0]) + 33;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(h_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, h_str);
	_strcat(err, ": Syntax error!: \"");
	_strcat(err, args[0]);
	_strcat(err, "\" Not correct\n");

	free(h_str);
	return (err);
}
