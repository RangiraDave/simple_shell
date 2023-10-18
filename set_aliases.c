#include "shell.h"

/**
 * set_alias - This function is responsible for configuring
 * aliases within the shell. It can be used to either update
 * an existing alias identified by 'var-name' with a new 'value'
 * or to create acompletely new alias using 'name' and 'value'.
 *
 * @var_name: The name of the alias.
 * @value: The value of the alias. It should start with an '='character.
 */

void set_alias(char *var_name, char *value)
{
	alias_list *temp = aliases;
	int len, j, k;
	char *new_value;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[k++] = value[j];
	}
	new_value[k] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->a_node) == 0)
		{
			free(temp->a_value);
			temp->a_value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, var_name, new_value);
}
