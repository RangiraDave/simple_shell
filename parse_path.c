#include "shell.h"

char *fill_path_dir(char *path);
list_t *path_directory(char *path);

/**
 * get_path - Searches for a command in the PATH.
 *
 * @command: The command to look for.
 *
 * Return: If there's an error or the command cannot be located,
 * it returns NULL. Otherwise, it returns the full
 * pathname of the command.
 */

char *get_path(char *command)
{
	char **way, *t;
	list_t *directories, *head;
	struct stat xy;

	way = _getenv("PATH");
	if (!way || !(*way))
		return (NULL);
	directories = path_directory(*way + 5);
	head = directories;
	while (directories)
	{
		t = malloc(_strlen(directories->node) + _strlen(command) + 2);
		if (!t)
			return (NULL);

		_strcpy(t, directories->node);
		_strcat(t, "/");
		_strcat(t, command);
		if (stat(t, &xy) == 0)
		{
			free_list(head);
			return (t);
		}
		directories = directories->next;
		free(t);
	}
	free_list(head);

	return (NULL);
}

/**
 * fill_path_directory - This function creates a modified copy of the
 * peth by replacing
 * any leading, saandwiched, or trailing colons (:) with the current
 * working directory.
 *
 * @path: The colon-separated list of directories.
 *
 * Return: The modified copy of the path.
 */

char *fill_path_directory(char *path)
{
	int x, len = 0;
	char *way_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (x = 0; path[x]; x++)
	{
		if (path[x] == ':')
		{
			if (path[x + 1] == ':' || x == 0 || path[x + 1] == '\0')
				len += _strlen(pwd) + 1;
			else
				len++;
		}
		else
			len++;
	}
	way_copy = malloc(sizeof(char) * (len + 1));
	if (!way_copy)
		return (NULL);
	way_copy[0] = '\0';
	for (x = 0; path[x]; x++)
	{
		if (path[x] == ':')
		{
			if (x == 0)
			{
				_strcat(way_copy, pwd);
				_strcat(way_copy, ":");
			}
			else if (path[x + 1] == ':' || path[x + 1] == '\0')
			{
				_strcat(way_copy, ":");
				_strcat(way_copy, pwd);
			}
			else
				_strcat(way_copy, ":");
		}
		else
		{
			_strncat(way_copy, &path[x], 1);
		}
	}
	return (way_copy);
}

/**
 * path_directory - Splits colon-separated directories and puts them
 * into a linked list.
 *
 * @path: Pointer to the list of directories.
 *
 * Return: A pointer to the head of a linked list.
 */

list_t *path_directory(char *path)
{
	int ind;
	char **directories, *way_copy;
	list_t *head = NULL;

	way_copy = fill_path_directory(path);
	if (!way_copy)
		return (NULL);
	directories = _strtok(way_copy, ":");
	free(way_copy);
	if (!directories)
		return (NULL);

	for (ind = 0; directories[ind]; ind++)
	{
		if (add_node_end(&head, directories[ind]) == NULL)
		{
			free_list(head);
			free(directories);
			return (NULL);
		}
	}

	free(directories);

	return (head);
}
