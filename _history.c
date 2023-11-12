#include "shell.h"

/**
 * for_history_file - gets the history file
 * @infom: parameter struct
 *
 * Return: allocated string containg history file
 */

char *for_history_file(info_t *infom)
{
	char *buffer, *direction;

	direction = for_getenvv(infom, "HOME=");
	if (!direction)
		return (NULL);
	buffer = malloc(sizeof(char) *
			(for_strlength(dir) + for_strlenght(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	for_strcpy(buffer, direction);
	for_strcat(buffer, "/");
	for_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * for_write_history - creates a file, or appends to an existing file
 * @infom: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int for_write_history(info_t *infom)
{
	ssize_t fdd;
	char *filename = for_history_file(infom);
	list_t *nodes = NULL;

	if (!filename)
		return (-1);

	fdd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fdd == -1)
		return (-1);
	for (nodes = infom->my_history; nodes; nodes = nodes->next)
	{
		for_putsfd(nodes->str, fdd);
		for_putfd('\n', fdd);
	}
	for_putfd(BUF_FLUSH, fdd);
	close(fdd);
	return (1);
}

/**
 * for_read_history - used to read history from file
 * @infom: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int for_read_history(info_t *infom)
{
	int i, last = 0, forlinecount = 0;
	ssize_t fdd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = for_history_file(infom);

	if (!filename)
		return (0);

	fdd = open(filename, O_RDONLY);
	free(filename);
	if (fdd == -1)
		return (0);
	if (!fstat(fdd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fdd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fdd);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buf[i] = 0;
			to_build_history_list(infom, buffer + last, forlinecount++);
			last = i + 1;
		}
	if (last != i)
		to_build_history_list(infom, buffer + last, forlinecount++);
	free(buffer);
	infom->forhistcount = forlinecount;
	while (infom->forhistcount-- >= HIST_MAX)
		for_delete_node_at_index(&(infom->my_history), 0);
	to_renumber_history(infom);
	return (infom->forhistcount);
}

/**
 * to_build_history_list - adds entry to a history linked list
 * @infom: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @forlinecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int to_build_history_list(info_t *infom, char *buffer, int forlinecount)
{
	list_t *nodes = NULL;

	if (infom->my_history)
		nodes = info->history;
	for_add_node_end(&nodes, buffer, forlinecount);

	if (!infom->my_history)
		infom->my_history = nodes;
	return (0);
}

/**
 * to_renumber_history - renumbers the history linked list after changes
 * @infom: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int to_renumber_history(info_t *infom)
{
	list_t *nodes = infom->my_history;
	int i = 0;

	while (nodes)
	{
		nodes->number = i++;
		nodes = nodes->next;
	}
	return (infom->forhistcount = i);
}


