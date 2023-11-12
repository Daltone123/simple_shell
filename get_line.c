#include "shell.h"

/**
 * to_input_buffer - is a buffer chained commands
 * @infom: parameter struct
 * @buffer: address of buffer
 * @length: address of length variable
 *
 * Return: bytes read
 */
ssize_t to_input_buffer(info_t *infom, char **buffer, size_t *length)
{
	ssize_t r = 0;
	size_t length_p = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, for_sigintHandler);
#if USE_GETLINE
		r = getline(buffer, &length_p, stdin);
#else
		r = for_getline(infom, buffer, &length_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}
			infom->linecount_flags = 1;
			for_removing_comments(*buffer);
			to_build_history_list(infom, *buffer, infom->forhistcount++);
			{
				*length = r;
				infom->cmd_buffer = buffer;
			}
		}
	}
	return (r);
}

/**
 * for_get_input - used to get a line minus the newline
 * @infom: parameter struct
 *
 * Return: bytes read
 */
ssize_t for_get_input(info_t *infom)
{
	static char *buffer;
	static size_t i, j, length;
	ssize_t r = 0;
	char **buffer_p = &(infom->arg), *pp;

	for_putchar(BUF_FLUSH);
	r = to_input_buffer(infom, &buffer, &length);
	if (r == -1)
		return (-1);
	if (length)
	{
		j = i;
		pp = buffer + i;

		to_check_chain(infom, buffer, &j, i, length);
		while (j < length)
		{
			if (for_chain(infom, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= length)
		{
			i = length = 0;
			infom->cmdbuftype = CMD_NORM;
		}

		*buffer_p = pp;
		return (for_strlength(pp));
	}

	*buffer_p = buffer;
	return (r);
}

/**
 * to_read_buf - reads a buffer
 * @infom: parameter struct
 * @buffer: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t to_read_buf(info_t *infom, char *buffer, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(infom->to_readfd, buffer, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * for_getline - gets the next line of input from STDIN
 * @infom: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @len: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int for_getline(info_t *infom, char **ptr, size_t *len)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, length;
	size_t k;
	ssize_t r = 0, s = 0;
	char *pp = NULL, *new_p = NULL, *c;

	pp = *ptr;
	if (pp && len)
		s = *len;
	if (i == length)
		i = length = 0;

	r = to_read_buf(infom, buffer, &length);
	if (r == -1 || (r == 0 && length == 0))
		return (-1);

	c = for_strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : length;
	new_p = to_realloc(pp, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (pp ? free(pp), -1 : -1);

	if (s)
		for_strncat(new_p, buffer + i, k - i);
	else
		for_strncpy(new_p, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	pp = new_p;

	if (len)
		*len = s;
	*ptr = pp;
	return (s);
}

/**
 * for_sigintHandler - blocks ctrl-C
 * @sig_number: the signal number
 *
 * Return: void
 */
void for_sigintHandler(__attribute__((unused))int sig_number)
{
	for_puts("\n");
	for_puts("$ ");
	for_putchar(BUF_FLUSH);
}

