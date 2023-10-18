#include "shell.h"

int shell_env(char **args, char __attribute__((__unused__)) **front);
int shell_setenv(char **args, char __attribute__((__unused__)) **front);
int shell_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shell_env - This function prints the current environment,
 * displaying variables in the format 'variable' = 'value'.
 *
 * @args: Arguments passed to the function.
 * @front:  A pointer
 *
 * Return: If successful,it returns -1; otherwise, it returns 0.
 */

int shell_env(char **args, char __attribute__((__unused__)) **front)
{
	int i;
	char xy = '\n';

	if (!environ)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, &xy, 1);
	}

	(void)args;
	return (0);
}

/**
 * shell_setenv - This function modifies the environment variable PATH.
 *
 * @args: Arguments passed to the function.
 * @front: A pointer
 * Description: args[1] is the name of the new or existing PATH variable,
 * args[2] is the value to set the new or changed variable to.
 *
 * Return: -1 on success or 0 on failure.
 */

int shell_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_enviro, *new_val;
	size_t bulk;
	int i;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_val = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_val)
		return (create_error(args, -1));
	_strcpy(new_val, args[0]);
	_strcat(new_val, "=");
	_strcat(new_val, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_val;
		return (0);
	}
	for (bulk = 0; environ[bulk]; bulk++)
		;
	new_enviro = malloc(sizeof(char *) * (bulk + 2));
	if (!new_enviro)
	{
		free(new_val);
		return (create_error(args, -1));
	}

	for (i = 0; environ[i]; i++)
		new_enviro[i] = environ[i];

	free(environ);
	environ = new_enviro;
	environ[i] = new_val;
	environ[i + 1] = NULL;

	return (0);
}

/**
 * shell_unsetenv - This function removes environment
 * variables from the PATH.
 * @args: Argments passed in the shell
 * @front: A pointer
 * Description: args[1] specifies the variable to be removed.
 *
 * Return: -1 on error or 0 on success.
 */

int shell_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_enviro;
	size_t bulk;
	int i, j;

	if (!args[0])
		return (create_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (bulk = 0; environ[bulk]; bulk++)
		;

	new_enviro = malloc(sizeof(char *) * bulk);
	if (!new_enviro)
		return (create_error(args, -1));

	for (i = 0, j = 0; environ[i]; i++)
	{
		if (*env_var == environ[i])
		{
			free(*env_var);
			continue;
		}
		new_enviro[j] = environ[i];
		j++;
	}
	free(environ);
	environ = new_enviro;
	environ[bulk - 1] = NULL;

	return (0);
}
