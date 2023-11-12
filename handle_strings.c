#include "shell.h"

/**
 * for_strlength - used to return the length of a string
 * @ss: the string whose length to check
 *
 * Return: integer length of string
 */
int for_strlength(char *ss)
{
	int i = 0;

	if (!ss)
		return (0);

	while (*ss++)
		i++;
	return (i);
}

/**
 * for_strcmp - performs lexicogarphic comparison of two strangs.
 * @ss1: the first strang
 * @ss2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int for_strcmp(char *ss1, char *ss2)
{
	while (*ss1 && *ss2)
	{
		if (*ss1 != *ss2)
			return (*ss1 - *ss2);
		ss1++;
		ss2++;
	}
	if (*ss1 == *ss2)
		return (0);
	else
		return (*ss1 < *ss2 ? -1 : 1);
}

/**
 * for_starting_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *for_starting_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * for_strcat - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *for_strcat(char *destination, char *source)
{
	char *rett = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (rett);
}

