#include "shell.h"

int token_length(char *str, char *delim);
int count_tok(char *str, char *delim);
char **_strtok(char *input, char *delim);

/**
 * token_length - This function calculates the length of first token.
 *
 * @str: The string to search in.
 * @delim: The delimiter to be used.
 *
 * Return: The delimiter index showing the end of
 * the intitial token pointed to the string
 */

int token_length(char *str, char *delim)
{
	int i = 0;
	int len = 0;

	while (*(str + i) && *(str + i) != *delim)
	{
		len++;
		i++;
	}

	return (len);
}

/**
 * count_tok - Counts the number of words with delimiter(tokens)
 * in the string.
 *
 * @str: The string to search in.
 * @delim: The delimiter to be used.
 *
 * Return: The number of tokens inside the string provided.
 */

int count_tok(char *str, char *delim)
{
	int i;
	int tkens = 0;
	int len = 0;

	for (i = 0; *(str + i); i++)
		len++;

	for (i = 0; i < len  ; i++)
	{
		if (*(str + i) != *delim)
		{
			tkens++;
			i += token_length(str + i, delim);
		}
	}

	return (tkens);
}

/**
 * _strtok - This function tokenizes a string.
 *
 * @input: The string to tokenize.
 * @delim: The delimiter to use.
 *
 * Return: A pointer to an array of the tokens.
 */

char **_strtok(char *input, char *delim)
{
	char **p;
	int i = 0, tkens, x, letters, y;

	tkens = count_tok(input, delim);
	if (tkens == 0)
		return (NULL);

	p = malloc(sizeof(char *) * (tkens + 2));
	if (!p)
		return (NULL);

	for (x = 0; x < tkens; x++)
	{
		while (input[i] == *delim)
			i++;

		letters = token_length(input + i, delim);

		p[x] = malloc(sizeof(char) * (letters + 1));
		if (!p[x])
		{
			for (i -= 1; i >= 0; i--)
				free(p[i]);
			free(p);
			return (NULL);
		}

		for (y = 0; y < letters; y++)
		{
			p[x][y] = input[i];
			i++;
		}

		p[x][y] = '\0';
	}
	p[x] = NULL;
	p[x + 1] = NULL;

	return (p);
}
