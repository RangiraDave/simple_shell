#include "shell.h"

void helper_all(void);
void helper_alias(void);
void helper_cd(void);
void helper_exit(void);
void helper_help(void);

/**
 * helper_all - This function serves as a utility for displaying
 * variable-related built-in shell commands.
 */

void helper_all(void)
{
	char *message = "Shell\nThe shell commands are defined inside.\n";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "Input 'help' to check the list.\nInput 'help name' to find out ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "check more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * helper_alias - This function provides detailed information about the
 * built-n commands 'alias'.
 */

void helper_alias(void)
{
	char *message = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, message, _strlen(message));
	message = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, message, _strlen(message));
	message = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * helper_cd - This function serves as an information indicator
 * for the shell's built-n command 'cd'.
 */

void helper_cd(void)
{
	char *message = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, message, _strlen(message));
	message = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, message, _strlen(message));
	message = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "after changing the directory.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * helper_exit - This function acts as an indicator for
 * the shell's built-in command 'exit'
 */

void helper_exit(void)
{
	char *message = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, message, _strlen(message));
	message = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, message, _strlen(message));
	message = " exit 0.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * helper_help - This function displays information
 * about the shell's built-in command 'help'.
 */

void helper_help(void)
{
	char *message = "help: help\n\tCheck all the Shell builtin commands.\n";

	write(STDOUT_FILENO, message, _strlen(message));
	message = "\n      help [BUILTIN NAME]\n\tCheck information about every ";
	write(STDOUT_FILENO, message, _strlen(message));
	message = "builtin command.\n";
	write(STDOUT_FILENO, message, _strlen(message));
}
