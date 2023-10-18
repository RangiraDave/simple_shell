#include "shell.h"

char **copy_env(void);
void free_env(void);
char **_getenv(const char *name);

/**
 * copy_env - This function creates a copy of the current environment.
 *
 * Return: If an error occurs, it returns NULL Otherwise,
 * a double pointer to the new copy.
 */

char **copy_env(void)
{
	char **new_enviro;
	size_t bulk;
	int ind;

	for (bulk = 0; environ[bulk]; bulk++)
		;

	new_enviro = malloc(sizeof(char *) * (bulk + 1));
	if (!new_enviro)
		return (NULL);

	for (ind = 0; environ[ind]; ind++)
	{
		new_enviro[ind] = malloc(_strlen(environ[ind]) + 1);

		if (!new_enviro[ind])
		{
			for (ind--; ind >= 0; ind--)
				free(new_enviro[ind]);
			free(new_enviro);
			return (NULL);
		}
		_strcpy(new_enviro[ind], environ[ind]);
	}
	new_enviro[ind] = NULL;

	return (new_enviro);
}

/**
 * free_env - This  function is responsible for freeing memory
 * associated with an environment copy.
 */

void free_env(void)
{
	int hint;

	for (hint = 0; environ[hint]; hint++)
		free(environ[hint]);
	free(environ);
}

/**
 * _getenv - This function retrievs  the value of environment variable
 * specified b 'var'.
 *
 * @name: The name of the environment variable to retrieve.
 *
 * Return: If the environment variable does not exist, NULL is returned.
 * Otherwise, a pointer to the environment variable's value is returned.
 */

char **_getenv(const char *name)
{
	int hin;
	int len;

	len = _strlen(name);
	for (hin = 0; environ[hin]; hin++)
	{
		if (_strncmp(name, environ[hin], len) == 0)
			return (&environ[hin]);
	}

	return (NULL);
}
