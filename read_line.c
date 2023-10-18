#include "shell.h"

/**
 * get_args - This function obtains commands from standard input
 *
 * @input: A pointer to store a buffer holding commamnd
 * @executed_ret: The output to be produced
 *
 * Return: A pointer if  it succeeds or NULL if it fails
 */

char *get_args(char *input, int *executed_ret)
{
	size_t x = 0;
	ssize_t read;
	char *shell_prompt = "cisfun$ ";

	if (input)
		free(input);

	read = _getline(&input, &x, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, shell_prompt, strlen(shell_prompt));
		return (get_args(input, executed_ret));
	}
	input[read - 1] = '\0';
	variable_replacement(&input, executed_ret);
	handle_input(&input, read);

	return (input);
}

/**
 * check_args - This function Identifies the existence of leading
 * ';', ';;', '&&', or '||' in the input.
 *
 * @args: a pointer
 *
 * Return: 0
 */

int check_args(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_error(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&args[i + 1], 2));
		}
	}
	return (0);
}
