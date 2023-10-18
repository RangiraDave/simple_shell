#include "shell.h"

/**
 * cmd_executor - This function executes a command in a child process.
 *
 * @args: An array of arguments.
 * @front: A double pointer to the starting args.
 *
 * Return: If an error occurs, it returns a corresponding error code.
 * Otherwise, it returns the exit value of the last executed command.
 */

int cmd_executor(char **args, char **front)
{
	pid_t fresh_pid;
	int profile, symbol = 0, r = 0;
	char *comd = args[0];

	if (comd[0] != '/' && comd[0] != '.')
	{
		symbol = 1;
		comd = get_path(comd);
	}
	if (!comd || (access(comd, F_OK) == -1))
	{
		if (errno == EACCES)
			r = (create_error(args, 126));
		else
			r = (create_error(args, 127));
	}
	else
	{
		fresh_pid = fork();
		if (fresh_pid == -1)
		{
			if (symbol)
				free(comd);
			perror("Error child:");
			return (1);
		}
		if (fresh_pid == 0)
		{
			execve(comd, args, environ);
			if (errno == EACCES)
				r = (create_error(args, 126));
			free_env();
			free_args(args, front);
			free_alias_list(aliases);
			_exit(r);
		}
		else
		{
			wait(&profile);
			ret = WEXITSTATUS(profile);
		}
	}
	if (symbol)
		free(comd);
	return (r);
}

/**
 * main - This function runs the entire simple shell command interpreter.
 *
 * @argc: The number of arguments provided to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */

char *shell_name = NULL;
int hist = 1;
alias_list *alias = NULL;

int main(int argc, char *argv[])
{
	int r = 0, ren;
	int *execute_ret = &ren;
	char *shell_prompt = "cisfun$ ", *new_line = "\n";

	signal(SIGINT, sig_handler);
	*execute_ret = 0;
	environ = copy_env();
	if (!environ)
		exit(-100);
	if (argc != 1)
	{
		r = file_commands(argv[1], execute_ret);
		free_env();
		free_alias_list(alias);
		return (*execute_ret);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (r != END_OF_FILE && r != EXIT)
			r = handle_args(execute_ret);
		free_env();
		free_alias_list(alias);
		return (*execute_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, shell_prompt, strlen(shell_prompt));
		r = handle_args(execute_ret);
		if (r == END_OF_FILE || r == EXIT)
		{
			if (r == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			free_alias_list(alias);
			exit(*execute_ret);
		}
	}

	free_env();
	free_alias_list(alias);
	return (*execute_ret);
}
