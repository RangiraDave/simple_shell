#include "shell.h"

char *get_args(char *line, int *executed_ret);
int invoke(char **args, char **front, int *executed_ret);
int execute_args(char **args, char **front, int *executed_ret);
int handle_args(int *executed_ret);
int check_args(char **args);

/**
 * invoke - Splits operators from commands and invokes them accordingly
 * @args: An array of arguments
 * @front: A double pointer
 * @executed_ret: The return value of the last executed command.
 *
 * Return: The value of the last executed command.
 */
int invoke(char **args, char **front, int *executed_ret)
{
	int r, i;

	if (!args[0])
		return (*executed_ret);
	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], "||", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = replace_aliases(args);
			r = execute_args(args, front, executed_ret);
			if (*executed_ret != 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (r);
			}
		}
		else if (_strncmp(args[i], "&&", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = replace_aliases(args);
			r = execute_args(args, front, executed_ret);
			if (*executed_ret == 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (r);
			}
		}
	}
	args = replace_aliases(args);
	r = execute_args(args, front, executed_ret);
	return (r);
}

/**
 * execute_args - Initiates the execution of a command
 * @args: An array of arguments.
 * @front: A double pointer
 * @executed_ret: The return value of the last executed command
 *
 * Return: The return value of the last executed command.
 */
int execute_args(char **args, char **front, int *executed_ret)
{
	int r, x;
	int (*builtin)(char **args, char **front);

	builtin = get_builtins(args[0]);

	if (builtin)
	{
		r = builtin(args + 1, front);
		if (r != EXIT)
			*executed_ret = r;
	}
	else
	{
		*executed_ret = cmd_executor(args, front);
		r = *executed_ret;
	}

	hist++;

	for (x = 0; args[x]; x++)
		free(args[x]);

	return (r);
}

/**
 * handle_args - Retrieves, invokes, and executes a command
 * @executed_ret: The return value of the last executed command
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2)
 * If the input cannot be tokenized - -1.
 * O/w - The exit value of the last executed command
 */
int handle_args(int *executed_ret)
{
	int r = 0, i;
	char **av, *input = NULL, **front;

	input = get_args(input, executed_ret);
	if (!input)
		return (END_OF_FILE);

	av = _strtok(input, " ");
	free(input);
	if (!av)
		return (r);
	if (check_args(av) != 0)
	{
		*executed_ret = 2;
		free_args(av, av);
		return (*executed_ret);
	}
	front = av;

	for (i = 0; av[i]; i++)
	{
		if (_strncmp(av[i], ";", 1) == 0)
		{
			free(av[i]);
			av[i] = NULL;
			r = invoke(av, front, executed_ret);
			av = &av[++i];
			i = 0;
		}
	}
	if (av)
		r = invoke(av, front, executed_ret);

	free(front);
	return (r);
}
