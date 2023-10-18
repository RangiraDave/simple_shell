#include "shell.h"

/**
 * print_alias - This function is used to display an alias in
 * the format name='value'.
 * @alias: A pointer to the alias.
 */

void print_alias(alias_list *alias)
{
	char *alias_string;
	int len = _strlen(alias->a_node) + _strlen(alias->a_value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->a_node);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->a_value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}
