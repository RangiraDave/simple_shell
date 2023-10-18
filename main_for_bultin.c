#include "shell.h"

int (*get_builtins(char *command))(char **args, char **front);
int shell_exit(char **args, char **front);
int shell_cd(char **args, char __attribute__((__unused__)) **front);
int shell_help(char **args, char __attribute__((__unused__)) **front);

/**
 * get_builtins - This function matches given cmd with its
 * corresponding builtin function.
 *
 * @command: String to find.
 *
 * Return: A pointer to the function corresponding the builtin.
 */

int (*get_builtins(char *command))(char **args, char **front)
{
	builtin_list fxs[] = {
		{ "exit", shell_exit },
		{ "env", shell_env },
		{ "setenv", shell_setenv },
		{ "unsetenv", shell_unsetenv },
		{ "cd", shell_cd },
		{ "alias", shell_alias },
		{ "help", shell_help },
		{ NULL, NULL }
	};
	int a;

	for (a = 0; fxs[a].b_node; a++)
	{
		if (_strcmp(fxs[a].b_node, command) == 0)
			break;
	}
	return (fxs[a].f);
}

/**
 * shell_exit - The function to use when exiting the shell.
 *
 * @args: An array of args to exit value.
 * @front: A double pointer to the starting args.
 *
 * Return: -3 for no arguments, 2 for invalid exit value,
 *  otherwise exits with the given status value.
 */

int shell_exit(char **args, char **front)
{
	unsigned int numb = 0, maxima = 1 << (sizeof(int) * 8 - 1);
	int x;
	int len_int = 10;

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			x = 1;
			len_int++;
		}
		for (; args[0][x]; x++)
		{
			if (x <= len_int && args[0][x] >= '0' && args[0][x] <= '9')
				numb = (numb * 10) + (args[0][x] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (numb > maxima - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_args(args, front);
	free_env();
	free_alias_list(aliases);
	exit(numb);
}

/**
 * shell_cd - Changes the current directory of the shell process
 * @args: An array of arguments
 * @front: A double pointer to the starting args
 *
 * Return: 2 if string given is not a directory
 * -1 when there is an error, otherwise - 0
 */

int shell_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **directory_info;
	char *fresh_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat directory;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	directory_info = malloc(sizeof(char *) * 2);
	if (!directory_info)
		return (-1);

	directory_info[0] = "OLDPWD";
	directory_info[1] = oldpwd;
	if (shell_setenv(direrectory_info, directory_info) == -1)
		return (-1);

	directory_info[0] = "PWD";
	directory_info[1] = pwd;
	if (shell_setenv(directory_info, directory_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, fresh_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(directory_info);
	return (0);
}

/**
 * shell_help - This function displays information about
 * shell builtin commands.
 *
 * @args: An array of arguments.
 * @front: A pointer to the starting args.
 *
 * Return: -1 When there is an error, otherwise - 0.
 */

int shell_help(char **args, char __attribute__((__unused__)) **front)
{
	char *look = args[0];

	if (!args[0])
		helper_all();
	else if (_strcmp(args[0], "alias") == 0)
		helper_alias();
	else if (_strcmp(args[0], "cd") == 0)
		helper_cd();
	else if (_strcmp(args[0], "exit") == 0)
		helper_exit();
	else if (_strcmp(args[0], "env") == 0)
		helper_env();
	else if (_strcmp(args[0], "setenv") == 0)
		helper_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		helper_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		helper_help();
	else
		write(STDERR_FILENO, look, _strlen(look));

	return (0);
}
