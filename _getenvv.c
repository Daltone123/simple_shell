#include "shell.h"

/**
 * for_get_environs - used to return the string array copy of our environ
 * @infom: is a Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **for_get_environs(info_t *infom)
{
	if (!infom->environ || infom->envv_change)
	{
		infom->environ = for_list_to_strings(infom->envv);
		infom->envv_change = 0;
	}

	return (infom->environ);
}

/**
 * for_unsetenvv - Remove an environment variable
 * @infom: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @varr: the string env var property
 */
int for_unsetenvv(info_t *infom, char *varr)
{
	list_t *nodes = infom->envv;
	size_t i = 0;
	char *p;

	if (!nodes || !varr)
		return (0);

	while (nodes)
	{
		pp = for_starting_with(nodes->str, varr);
		if (pp && *pp == '=')
		{
			infom->envv_change = for_delete_node_at_index(&(infom->envv), i);
			i = 0;
			nodes = infom->envv;
			continue;
		}
		node = nodes->next;
		i++;
	}
	return (infom->envv_change);
}

/**
 *for_setenvv - used to Initialize a new environment variable,
 *             or modify an existing one
 * @infom: is a Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @varr: the string env var property
 * @values: the string env var value
 *  Return: Always 0
 */
int for_setenvv(info_t *infom, char *varr, char *values)
{
	char *buf = NULL;
	list_t *nodes;
	char *pp;

	if (!varr || !values)
		return (0);

	buf = malloc(for_strlength(varr) + for_strlength(values) + 2);
	if (!buf)
		return (1);
	for_strcpy(buf, varr);
	for_strcat(buf, "=");
	for_strcat(buf, values);
	nodes = infom->envv;
	while (nodes)
	{
		pp = for_starting_with(nodes->str, varr);
		if (pp && *pp == '=')
		{
			free(nodes->str);
			nodes->str = buf;
			infom->envv_change = 1;
			return (0);
		}
		nodes = nodes->next;
	}
	for_add_node_end(&(infom->envv), buf, 0);
	free(buf);
	infom->envv_change = 1;
	return (0);
}


