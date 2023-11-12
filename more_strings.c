#include "shell.h"

/**
 * for_strcpy - use to copy a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *for_strcpy(char *destination, char *source)
{
	int i = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[i])
	{
		destination[i] = source[i];
		i++;
	}
	destination[i] = 0;
	return (destination);
}

/**
 * for_strdup - used to duplicate a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *for_strdup(const char *str)
{
	int len = 0;
	char *rett;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	rett = malloc(sizeof(char) * (len + 1));
	if (!rett)
		return (NULL);
	for (len++; len--;)
		rett[len] = *--str;
	return (rett);
}

/**
 * for_puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void for_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		for_putchar(str[i]);
		i++;
	}
}

/**
 * for_putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int for_putchar(char c)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;
	return (1);
}


