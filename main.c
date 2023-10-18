#include "shell.h"

char *name = NULL;
int hist = 1;
alias_list *aliases = NULL;

/**
 * main - This function runs the entire simple shell cmd interpreter.
 *
 * @argc: The number of arguments provided to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */

int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *execute_ret = &retn;
	char *prompt = "cisfun$ ", *new_line = "\n";

	signal(SIGINT, sig_handler);
	*execute_ret = 0;
	environ = copy_env();
	if (!environ)
		exit(-100);
	if (argc != 1)
	{
		ret = file_commands(argv[1], execute_ret);
		free_env();
		free_alias_list(aliases);
		return (*execute_ret);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = handle_args(execute_ret);
		free_env();
		free_alias_list(aliases);
		return (*execute_ret);
	}
	while (1)
	{
		write(STDOUT_FILENO, prompt, strlen(prompt));
		ret = handle_args(execute_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			free_alias_list(aliases);
			exit(*execute_ret);
		}
	}
	free_env();
	free_alias_list(aliases);
	return (*execute_ret);
}
