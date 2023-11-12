#include "shell.h"

/**
 * **to_strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @dd: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **to_strtow(char *str, char *dd)
{
	int i, j, k, m, numwords = 0;
	char **ss;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!dd)
		dd = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!deliminator(str[i], d) && (deliminator(str[i + 1], dd) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	ss = malloc((1 + numwords) * sizeof(char *));
	if (!ss)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (deliminator(str[i], dd))
			i++;
		k = 0;
		while (!deliminator(str[i + k], dd) && str[i + k])
			k++;
		ss[j] = malloc((k + 1) * sizeof(char));
		if (!ss[j])
		{
			for (k = 0; k < j; k++)
				free(ss[k]);
			free(ss);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			ss[j][m] = str[i++];
		ss[j][m] = 0;
	}
	ss[j] = NULL;
	return (ss);
}

/**
 * **to_strtow2 - splits a string into words
 * @str: the input string
 * @dd: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **to_strtow2(char *str, char dd)
{
	int i, j, k, m, numwords = 0;
	char **ss;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != dd && str[i + 1] == dd) ||
				    (str[i] != dd && !str[i + 1]) || str[i + 1] == dd)
			numwords++;
	if (numwords == 0)
		return (NULL);
	ss = malloc((1 + numwords) * sizeof(char *));
	if (!ss)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == dd && str[i] != dd)
			i++;
		k = 0;
		while (str[i + k] != dd && str[i + k] && str[i + k] != dd)
			k++;
		ss[j] = malloc((k + 1) * sizeof(char));
		if (!ss[j])
		{
			for (k = 0; k < j; k++)
				free(ss[k]);
			free(ss);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			ss[j][m] = str[i++];
		ss[j][m] = 0;
	}
	ss[j] = NULL;
	return (ss);
}


