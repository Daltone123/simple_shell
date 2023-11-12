#include "shell.h"

/**
 * for_chain - to test if current char in buffer is a chain delimeter
 * @infom: the parameter struct
 * @buffer: the char buffer
 * @pp: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int for_chain(info_t *infom, char *buffer, size_t *pp)
{
	size_t j = *pp;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		infom->cmdbuftype = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		infom->cmdbuftype = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		infom->cmdbuftype = CMD_CHAIN;
	}
	else
		return (0);
	*pp = j;
	return (1);
}

/**
 * to_check_chain - checks that should continue chaining based on last status
 * @infom: the parameter struct
 * @buffer: the char buffer
 * @pp: address of current position in buf
 * @i: starting position in buf
 * @length: length of buf
 *
 * Return: Void
 */
void to_check_chain(info_t *infom,
		char *buffer, size_t *pp, size_t i, size_t length)
{
	size_t j = *pp;

	if (infom->cmdbuftype == CMD_AND)
	{
		if (infom->status)
		{
			buffer[i] = 0;
			j = length;
		}
	}
	if (infom->cmdbuftype == CMD_OR)
	{
		if (!infom->status)
		{
			buffer[i] = 0;
			j = length;
		}
	}

	*pp = j;
}

/**
 * for_replacing_alias - used to replaces an aliases in the tokenized string
 * @infom: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int for_replacing_alias(info_t *infom)
{
	int i;
	list_t *nodes;
	char *pp;

	for (i = 0; i < 10; i++)
	{
		nodes = for_node_starts_with(infom->alias, infom->argv[0], '=');
		if (!nodes)
			return (0);
		free(infom->argv[0]);
		pp = for_strchr(nodes->str, '=');
		if (!pp)
			return (0);
		pp = for_strdup(pp + 1);
		if (!pp)
			return (0);
		infom->argv[0] = pp;
	}
	return (1);
}

/**
 * for_replacing_vars - used to replace vars in the tokenized string
 * @infom: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int for_replacing_vars(info_t *infom)
{
	int i = 0;
	list_t *nodes;

	for (i = 0; infom->argv[i]; i++)
	{
		if (infom->argv[i][0] != '$' || !infom->argv[i][1])
			continue;

		if (!for_strcmp(infom->argv[i], "$?"))
		{
			for_replacing_string(&(infom->argv[i]),
					for_strdup(for_converting_number(infom->status, 10, 0)));
			continue;
		}
		if (!for_strcmp(infom->argv[i], "$$"))
		{
			for_replacing_string(&(infom->argv[i]),
					for_strdup(for_converting_number(getpid(), 10, 0)));
			continue;
		}
		nodes = for_node_starts_with(infom->envv, &infom->argv[i][1], '=');
		if (nodes)
		{
			for_replacing_string(&(infom->argv[i]),
					for_strdup(for_strchr(nodes->str, '=') + 1));
			continue;
		}
		for_replacing_string(&infom->argv[i], for_strdup(""));

	}
	return (0);
}

/**
 * for_replacing_string - used to replace string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int for_replacing_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}



