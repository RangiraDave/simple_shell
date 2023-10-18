#include "shell.h"

void handle_input(char **line, ssize_t read);
ssize_t get_new_len(char *line);

/**
 * handle_input - This function divides the obtained line from standard
 * output into segments, adding to separate ";", "||",
 * and "&&" operators and replacing "#" with '\0'
 *
 * @line: A pointer to the line.
 * @read: Length of input.
 *
 * Description: This function modifies the input line to separate
 * segments and hndle comments.
 */

void handle_input(char **line, ssize_t read)
{
	char *last_line, *fresh_line;
	char prev, cur, next;
	size_t x, y;
	ssize_t new_length;

	new_length = get_new_length(*line);
	if (new_length == read - 1)
		return;
	fresh_line = malloc(new_length + 1);
	if (!fresh_line)
		return;
	y = 0;
	last_line = *line;
	for (x = 0; last_line[x]; x++)
	{
		cur = last_line[x];
		next = last_line[x + 1];
		if (x != 0)
		{
			prev = last_line[x - 1];
			if (cur == ';')
			{
				if (next == ';' && prev != ' ' && prev != ';')
				{
					fresh_line[y++] = ' ';
					fresh_line[y++] = ';';
					continue;
				}
				else if (prev == ';' && next != ' ')
				{
					fresh_line[y++] = ';';
					fresh_line[y++] = ' ';
					continue;
				}
				if (prev != ' ')
					fresh_line[j++] = ' ';
				fresh_line[y++] = ';';
				if (next != ' ')
					fresh_line[y++] = ' ';
				continue;
			}
			else if (cur == '&')
			{
				if (next == '&' && prev != ' ')
					fresh_line[y++] = ' ';
				else if (prev == '&' && next != ' ')
				{
					fresh_line[y++] = '&';
					fresh_line[y++] = ' ';
					continue;
				}
			}
			else if (cur == '|')
			{
				if (next == '|' && prev != ' ')
					fresh_line[y++]  = ' ';
				else if (prev == '|' && next != ' ')
				{
					fresh_line[y++] = '|';
					fresh_line[y++] = ' ';
					continue;
				}
			}
		}
		else if (cur == ';')
		{
			if (x != 0 && last_line[x - 1] != ' ')
				fresh_line[y++] = ' ';
			fresh_line[y++] = ';';
			if (next != ' ' && next != ';')
				fresh_line[y++] = ' ';
			continue;
		}
		fresh_line[y++] = last_line[x];
	}
	fresh_line[y] = '\0';

	free(*line);
	*line = fresh_line;
}

/**
 * get_new_len - This function calculates the new length of a line
 * after being divided by such as ";", "||", or "#".
 *
 * @line: The line to be counted.
 *
 * Return: The new length of line after proccessing.
 *
 * Description: This function shortens lines
 * that contain '#' comments using '\0'
 */

ssize_t get_new_len(char *line)
{
	size_t x;
	ssize_t new_length = 0;
	char cur, next;

	for (x = 0; line[x]; x++)
	{
		cur = line[x];
		next = line[x + 1];
		if (cur == '#')
		{
			if (x == 0 || line[x - 1] == ' ')
			{
				line[] = '\0';
				break;
			}
		}
		else if (x != 0)
		{
			if (cur == ';')
			{
				if (next == ';' && line[x - 1] != ' ' && line[x - 1] != ';')
				{
					new_length += 2;
					continue;
				}
				else if (line[x - 1] == ';' && next != ' ')
				{
					new_length += 2;
					continue;
				}
				if (line[x - 1] != ' ')
					new_length++;
				if (next != ' ')
					new_length++;
			}
			else
				find_op(&line[x], &new_length);
		}
		else if (cur == ';')
		{
			if (x != 0 && line[x - 1] != ' ')
				new_length++;
			if (next != ' ' && next != ';')
				new_length++;
		}
		new_length++;
	}
	return (new_length);
}
