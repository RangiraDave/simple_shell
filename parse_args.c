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
	int r, ind;

	if (!args[0])
		return (*executed_ret);
	for (ind = 0; args[ind]; ind++)
	{
		if (_strncmp(args[ind], "||", 2) == 0)
		{
			free(args[ind]);
			args[index] = NULL;
			args = replace_aliases(args);
			r = execute_args(args, front, executed_ret);
			if (*executed_ret != 0)
			{
				args = &args[++ind];
				ind = 0;
			}
			else
			{
				for (ind++; args[ind]; ind++)
					free(args[ind]);
				return (r);
			}
		}
		else if (_strncmp(args[ind], "&&", 2) == 0)
		{
			free(args[ind]);
			args[ind] = NULL;
			args = replace_aliases(args);
			r = execute_args(args, front, executed_ret);
			if (*executed_ret == 0)
			{
				args = &args[++ind];
				ind = 0;
			}
			else
			{
				for (ind++; args[ind]; ind++)
					free(args[ind]);
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
	int r = 0, ind;
	char **ar, *bulk = NULL, **front;

	line = get_args(line, executed_ret);
	if (!bulk)
		return (END_OF_FILE);

	ar = _strtok(bulk, " ");
	free(bulk);
	if (!args)
		return (r);
	if (check_args(ar) != 0)
	{
		*executed_ret = 2;
		free_args(ar, ar);
		return (*executed_ret);
	}
	front = ar;

	for (ind = 0; ar[ind]; ind++)
	{
		if (_strncmp(ar[ind], ";", 1) == 0)
		{
			free(ar[ind]);
			ar[ind] = NULL;
			r = invoke(ar, front, executed_ret);
			ar = &ar[++ind];
			ind = 0;
		}
	}
	if (ar)
		r = invoke(ar, front, executed_ret);

	free(front);
	return (r);
}
