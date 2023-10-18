#include "shell.h"

/**
 * find_op - This function checks for the existence of logical
 * operators "||" or "&&"
 *
 * @line:  character pointer to the input string.
 * @new_len: A pointer to store the new length after processing.
 * Return: Nothing.
 */

void find_op(char *line, ssize_t *new_len)
{
	char prev, cur, following;

	prev = *(line - 1);
	cur = *line;
	following = *(line + 1);
	if (cur == '&')
	{
		if (following == '&' && prev != ' ')
			(*new_len)++;
		else if (prev == '&' && following != ' ')
			(*new_len)++;
	}
	else if (cur == '|')
	{
		if (following == '|' && prev != ' ')
			(*new_len)++;
		else if (prev == '|' && following != ' ')
			(*new_len)++;
	}
}
