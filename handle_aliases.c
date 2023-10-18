#include "shell.h"

int shell_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_list *alias);

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
	alias_list *t = aliases;
	int x, r = 0;
	char *val;

	if (!args[0])
	{
		while (t)
		{
			print_alias(t);
			t = t->next;
		}
		return (r);
	}
	for (x = 0; args[x]; x++)
	{
		t = aliases;
		val = _strchr(args[x], '=');
		if (!val)
		{
			while (t)
			{
				if (_strcmp(args[x], t->a_node) == 0)
				{
					print_alias(t);
					break;
				}
				t = t->next;
			}
			if (!t)
				r = create_error(args + x, 1);
		}
		else
			set_alias(args[x], val);
	}
	return (r);
}

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
	alias_list *t = aliases;
	int leng, n, m;
	char *new_val;

	*value = '\0';
	value++;
	leng = _strlen(value) - _strspn(value, "'\"");
	new_val = malloc(sizeof(char) * (leng + 1));
	if (!new_val)
		return;
	for (n = 0, m = 0; value[n]; n++)
	{
		if (value[n] != '\'' && value[n] != '"')
			new_val[m++] = value[n];
	}
	new_val[m] = '\0';
	while (t)
	{
		if (_strcmp(var_name, t->a_node) == 0)
		{
			free(t->a_value);
			t->a_value = new_val;
			break;
		}
		t = t->next;
	}
	if (!t)
		add_alias_end(&aliases, var_name, new_val);
}

/**
 * print_alias - This function is used to display an alias in
 * the format name='value'.
 * @alias: A pointer to the alias.
 */

void print_alias(alias_list *alias)
{
	char *alias_str;
	int leng = _strlen(alias->a_node) + _strlen(alias->a_value) + 4;

	alias_str = malloc(sizeof(char) * (leng + 1));
	if (!alias_str)
		return;
	_strcpy(alias_str, alias->a_node);
	_strcat(alias_str, "='");
	_strcat(alias_str, alias->a_value);
	_strcat(alias_str, "'\n");

	write(STDOUT_FILENO, alias_str, leng);
	free(alias_str);
}

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
	alias_list *t;
	int x;
	char *new_val;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (x = 0; args[x]; x++)
	{
		t = aliases;
		while (t)
		{
			if (_strcmp(args[x], t->a_node) == 0)
			{
				new_val = malloc(sizeof(char) * (_strlen(t->a_value) + 1));
				if (!new_val)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_val, t->a_value);
				free(args[x]);
				args[x] = new_val;
				x--;
				break;
			}
			t = t->next;
		}
	}

	return (args);
}
