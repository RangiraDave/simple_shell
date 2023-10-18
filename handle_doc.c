#include "shell.h"

void helper_env(void);
void helper_setenv(void);
void helper_unsetenv(void);
void helper_history(void);

/**
 * helper_env - This function provieds detailed infromation about
 * the shell's built-in command 'env'.
 */

void helper_env(void)
{
	char *message = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * helper_setenv - This function offers detailed information about
 * the shell's built-in command 'setenv'.
 */

void helper_setenv(void)
{
	char *message = "setenv: setenv [VARIABLE] [VALUE]\n\tCreates a new";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "\tWhen it fails, it prints a message to the stderr.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * helper_unsetenv - This function provides detailed information about
 * the shell's built-in command 'unsetenv'.
 */

void helper_unsetenv(void)
{
	char *message = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "environmental variable.\n\n\tWhen it fails, it prints a ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "message to stderr.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}
