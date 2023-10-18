#include "shell.h"

int num_len(int num);
char *_atoi(int num);
int create_error(char **args, int er);

/**
 * num_len - This function calculates the number of digits
 * in a provided number.
 * @num: The number to count digits in.
 * Return:  The length of the input number.
 */

int num_len(int num)
{
	unsigned int numb1;
	int leng = 1;

	if (num < 0)
	{
		leng++;
		numb1 = num * -1;
	}
	else
	{
		numb1 = num;
	}
	while (numb1 > 9)
	{
		leng++;
		numb1 /= 10;
	}

	return (leng);
}

/**
 * _atoi - This function converts an integer into its corresponding
 * string representation.
 *
 * @num: The integer to be converted.
 *
 * Return: A string to represent the integer.
 */

char *_atoi(int num)
{
	char *buff;
	int leng = num_len(num);
	unsigned int num_x;

	buff = malloc(sizeof(char) * (leng + 1));
	if (!buff)
		return (NULL);

	buff[leng] = '\0';

	if (num < 0)
	{
		num_x = num * -1;
		buff[0] = '-';
	}
	else
	{
		num_x = num;
	}

	leng--;
	do {
		buff[leng] = (num_x % 10) + '0';
		num_x /= 10;
		leng--;
	} while (num_x > 0);

	return (buff);
}

/**
 * create_error - This function generates an error message and returns
 * the specified error value.
 *
 * @args: Array of arguments
 * @e_value: The value of the error
 *
 * Return: The value of the error.
 */

int create_error(char **args, int e_value)
{
	char *err;

	switch (e_value)
	{
		case -1:
			err = env_error(args);
			break;
		case 1:
			err = alias_error(args);
			break;
		case 2:
			if (*(args[0]) == 'e')
				err = exit_error(++args);
			else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
				err = syntax_error(args);
			else
				err = cd_error(args);
			break;
		case 126:
			err = error_126(args);
			break;
		case 127:
			err = error_127(args);
			break;
	}
	write(STDERR_FILENO, err, _strlen(err));

	if (err)
		free(err);
	return (e_value);

}
