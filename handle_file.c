#include "shell.h"

int can_not_open(char *file_path);
int file_commands(char *file_path, int *executed_ret);

/**
 * can_not_open - This function prints an error message when a file cannot be
 * opened due to its non-existence or insufficient permissions.
 *
 * @file_path: The path to the file in question.
 *
 * Return: 127 (Error code indicating file cannot be opened).
 */

int can_not_open(char *file_path)
{
	char *err, *hist_string;
	int length;

	hist_string = _atoi(hist);
	if (!hist_string)
		return (127);
	length = _strlen(name) + _strlen(hist_string) + _strlen(file_path) + 16;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(hist_string);
		return (127);
	}
	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_string);
	_strcat(err, ": Can not open ");
	_strcat(err, file_path);
	_strcat(err, "\n");

	free(hist_string);
	write(STDERR_FILENO, err, length);
	free(err);
	return (127);
}

/**
 * file_commands - This function receives a file and begins
 * executing the commands stored inside it.
 *
 * @file_path: Path to the file
 * @executed_ret: Return value of the last executed command
 *
 * Return: If the file cannot be opend, it reurns 127.
 * If memory allocation fails, it returns -1.
 * Otherwise, it  returns the value of the last command executed.
 */

int file_commands(char *file_path, int *executed_ret)
{
	ssize_t held, b_read, x;
	unsigned int line_held = 0;
	unsigned int old_bulk = 120;
	char *line, **args, **front, buffer[120];
	int r;

	hist = 0;
	held = open(file_path, O_RDONLY);
	if (held == -1)
	{
		*executed_ret = can_not_open(file_path);
		return (*executed_ret);
	}
	line = malloc(sizeof(char) * old_bulk);
	if (!line)
		return (-1);
	do {
		b_read = read(held, buffer, 119);
		if (b_read == 0 && line_held == 0)
			return (*executed_ret);
		buffer[b_read] = '\0';
		line_held += b_read;
		line = _realloc(line, old_bulk, line_held);
		_strcat(line, buffer);
		old_bulk = line_held;
	} while (b_read);
	for (x = 0; line[x] == '\n'; x++)
		line[x] = ' ';
	for (; x < line_held; x++)
	{
		if (line[x] == '\n')
		{
			line[x] = ';';
			for (x += 1; x < line_held && line[x] == '\n'; x++)
				line[x] = ' ';
		}
	}
	variable_replacement(&line, executed_ret);
	handle_input(&line, line_held);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*executed_ret = 2;
		free_args(args, args);
		return (*executed_ret);
	}
	front = args;

	for (x = 0; args[x]; x++)
	{
		if (_strncmp(args[x], ";", 1) == 0)
		{
			free(args[x]);
			args[x] = NULL;
			r = invoke(args, front, executed_ret);
			args = &args[++x];
			x = 0;
		}
	}

	r = invoke(args, front, executed_ret);
	free(front);
	return (r);
}
