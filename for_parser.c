#include "shell.h"

/**
 * is_cmd - used to determine if a file is an executable command
 * @infom: the info struct
 * @paths: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *infom, char *paths)
{
	struct stat stt;

	(void)infom;
	if (!paths || stat(paths, &stt))
		return (0);

	if (stt.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * for_dup_chars - duplicating characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *for_dup_chars(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buffer[k++] = pathstr[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * for_finding_path - finds this cmd in the PATH string
 * @infom: the information struct
 * @pathstr: the PATH string
 * @cmdd: the command to find
 *
 * Return: full path of cmd if found or NULL
 */
char *for_finding_path(info_t *infom, char *pathstr, char *cmdd)
{
	int i = 0, curr_position = 0;
	char *paths;

	if (!pathstr)
		return (NULL);
	if ((for_strlength(cmdd) > 2) && for_starting_with(cmdd, "./"))
	{
		if (is_cmd(infom, cmdd))
			return (cmdd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			paths = for_dup_chars(pathstr, curr_position, i);
			if (!*paths)
				for_strcat(paths, cmdd);
			else
			{
				for_strcat(paths, "/");
				for_strcat(paths, cmdd);
			}
			if (is_cmd(infom, paths))
				return (paths);
			if (!pathstr[i])
				break;
			curr_position = i;
		}
		i++;
	}
	return (NULL);
}


