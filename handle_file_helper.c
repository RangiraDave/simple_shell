#include "shell.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *executed_ret);

/**
 * free_args - This function deallocates the memory occupied by the args.
 * @args: A null-terminated array of commands/arguments.
 * @front: A double pointer to the beginning of args.
 */
void free_args(char **args, char **front)
{
	size_t x;

	for (x = 0; args[x] || args[x + 1]; x++)
		free(args[x]);

	free(front);
}

/**
 * get_pid - Retrieves the process ID of the current program
 * Description: This function retrieves the process ID of the current program
 * by reading the "/proc/self/stat" file. It allocates memory for a buffer,
 * opens the file, reads the process information into the buffer,
 * extracts the process ID from the buffer, and returns it as a string.
 * If any error occurs during the process, the function returns NULL.
 *
 * Return: The function returns either the current process ID or
 * NULL if there is a failure.
 */
char *get_pid(void)
{
	size_t x = 0;
	char *buff;
	ssize_t held;

	held = open("/proc/self/stat", O_RDONLY);
	if (held == -1)
	{
		perror("Can not read the file");
		return (NULL);
	}
	buff = malloc(120);
	if (!buff)
	{
		close(held);
		return (NULL);
	}
	read(held, buff, 120);
	while (buff[x] != ' ')
		x++;
	buff[x] = '\0';

	close(held);
	return (buff);
}

/**
 * get_env_value - This function gets the value corresponding
 * to an environment variable.
 *
 * @beginning: The environment variable to find
 * @len: The length of the environment variable to find
 *
 * Return: An empty string when no variable found,
 * Otherwise, the value of the environment variable
 */

char *get_env_value(char *beginning, int len)
{
	char **variable_address;
	char *replaced = NULL, *t, *variable;

	variable = malloc(len + 1);
	if (!variable)
		return (NULL);
	variable[0] = '\0';
	_strncat(variable, beginning, len);

	variable_address = _getenv(variable);
	free(variable);
	if (variable_address)
	{
		t = *variable_address;
		while (*t != '=')
			t++;
		t++;
		replaced = malloc(_strlen(t) + 1);
		if (replaced)
			_strcpy(replaced, t);
	}

	return (replaced);
}

/**
 * variable_replacement - Manages how variables are replaced.
 * @line: An array containing the command and arguments
 * @executed_ret: A pointer to a return value of the last executed cmd
 *
 * Description:This function performs variable replacement by replacing "$$"
 * with the current process ID, "$?" with the return value of the last executed
 * program, and environmental variables prefixed with "$" with
 * their respective values
 */

void variable_replacement(char **line, int *executed_ret)
{
	int n, m = 0, length;
	char *replaced = NULL;
	char *a_line = NULL;
	char *b_line;

	a_line = *line;
	for (n = 0; a_line[n]; n++)
	{
		if (a_line[n] == '$' && a_line[n + 1] &&
				a_line[n + 1] != ' ')
		{
			if (a_line[n + 1] == '$')
			{
				replaced = get_pid();
				m = n + 2;
			}
			else if (a_line[n + 1] == '?')
			{
				replaced = _atoi(*executed_ret);
				m = n + 2;
			}
			else if (a_line[n + 1])
			{
				for (m = n + 1; a_line[m] &&
						a_line[m] != '$' &&
						a_line[m] != ' '; m++)
					;
				length = m - (n + 1);
				replaced = get_env_value(&a_line[n + 1], length);
			}
			b_line = malloc(n + _strlen(replaced)
					  + _strlen(&a_line[m]) + 1);
			if (!line)
				return;
			b_line[0] = '\0';
			_strncat(b_line, a_line, n);
			if (replaced)
			{
				_strcat(b_line, replaced);
				free(replaced);
				replaced = NULL;
			}
			_strcat(b_line, &a_line[m]);
			free(a_line);
			*line = b_line;
			a_line = b_line;
			n = -1;
		}
	}
}
