#include "shell.h"

/**
 * shell_alias - This built-in command serves the purpose of managing
 * aliases within the shell.
 *
 * @args: An array containing command arguments.
 * @front: A double pointer to the start of arguments array.
 *
 * Return: If an error occurs, it returns -1.
 *         Otherwise, it returns 0.
 */

int shell_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_list *temp = aliases;
	int i, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		value = _strchr(args[i], '=');
		if (!value)
		{
			while (temp)
			{
				if (_strcmp(args[i], temp->a_node) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = create_error(args + i, 1);
		}
		else
			set_alias(args[i], value);
	}
	return (ret);
}
