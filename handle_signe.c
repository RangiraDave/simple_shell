#include "shell.h"

/**
 * sig_handler - This function prints a new prompt related
 * to the given signal.
 *
 * @sig: The signal to be handled.
 */

void sig_handler(int sig)
{
	char *shell_prompt = "\n# ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, shell_prompt, strlen(shell_prompt));
}
