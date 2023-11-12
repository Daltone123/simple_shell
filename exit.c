#include "shell.h"

/**
 **for_strncpy - copies a string
 *@destination: the destination string to be copied to
 *@source: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *for_strncpy(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	while (source[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **for_strncat - used to concatenates two strings
 *@destination: the first string
 *@source: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *for_strncat(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < n)
	{
		destination[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		destination[i] = '\0';
	return (s);
}

/**
 **for_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *for_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}


