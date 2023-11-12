#include "shell.h"

/**
 * to_interact - returns true if shell is interactive mode
 * @infom: struct address
 *
 * Return: 1 if the interactive mode, 0 otherwise
 */
int to_interact(info_t *infom)
{
	return (isatty(STDIN_FILENO) && infom->to_readfd <= 2);
}

/**
 * deliminator - checks if character is a delimeter
 * @c: the char to check
 * @delima: the delimeter string
 * Return: 1 if true, 0 if false
 */
int deliminator(char c, char *delima)
{
	while (*delima)
		if (*delima++ == c)
			return (1);
	return (0);
}

/**
 * alphabetic - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int alphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * for_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int for_atoi(char *s)
{
	int i, sign = 1, flags = 0, result;
	unsigned int output = 0;

	for (i = 0; s[i] != '\0' && flags != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flags = 1;
			output *= 10;
			output += (s[i] - '0');
		}
		else if (flags == 1)
			flags = 2;
	}

	if (sign == -1)
		result = -output;
	else
		result = output;

	return (result);
}


