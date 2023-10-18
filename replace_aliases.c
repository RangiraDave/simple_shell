#include "shell.h"

/**
 * replace_aliases - replaces all arguments with theire matching
 * alias with their value.
 *
 * @args: An array or arguments.
 *
 * Return: Array of arguments.
 */

char **replace_aliases(char **args)
{
	alias_list *temp;
	int i;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[i], temp->a_node) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(temp->a_value) + 1));
				if (!new_value)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_value, temp->a_value);
				free(args[i]);
				args[i] = new_value;
				i--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}
