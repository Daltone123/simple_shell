#include "shell.h"

/**
 * for_eputs - used to print an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void for_eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		for_eputchar(str[i]);
		i++;
	}
}

/**
 * for_eputchar - used to writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int for_eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * for_putfd - writes the character c to given fd
 * @c: The character to print
 * @fdd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int for_putfd(char c, int fdd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fdd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * for_putsfd - ised to print an input string
 * @str: the string to be printed
 * @fdd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int for_putsfd(char *str, int fdd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += for_putfd(*str++, fdd);
	}
	return (i);
}


