#include "shell.h"

/**
 * for_myhistory - used to display the history list,
 * one command by line, preceded
 *              with line numbers, starting at 0.
 * @infom: is a Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int for_myhistory(info_t *infom)
{
	for_printing_list(infom->my_history);
	return (0);
}

/**
 * for_unset_alias - setting alias to string
 * @infom: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int for_unset_alias(info_t *infom, char *str)
{
	char *pp, c;
	int rett;

	pp = for_strchr(str, '=');
	if (!pp)
		return (1);
	c = *pp;
	*pp = 0;
	rett = for_delete_node_at_index(&(infom->alias),
		for_get_node_index(infom->alias, for_node_starts_with(infom->alias, str, -1)));
	*pp = c;
	return (rett);
}

/**
 * for_set_alias - setting alias to string
 * @infom: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int for_set_alias(info_t *infom, char *str)
{
	char *pp;

	pp = for_strchr(str, '=');
	if (!pp)
		return (1);
	if (!*++pp)
		return (for_unset_alias(infom, str));

	for_unset_alias(infom, str);
	return (for_add_node_end(&(infom->alias), str, 0) == NULL);
}

/**
 * for_printing_alias - prints an alias string
 * @nodes: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int for_printing_alias(list_t *nodes)
{
	char *pp = NULL, *a = NULL;

	if (nodes)
	{
		pp = for_strchr(nodes->str, '=');
		for (a = nodes->str; a <= pp; a++)
		for_putchar(*a);
		for_putchar('\'');
		for_puts(pp + 1);
		for_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * for_myalias - it is used to mimic the alias builtin (manning alias)
 * @infom: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int for_myalias(info_t *infom)
{
	int i = 0;
	char *pp = NULL;
	list_t *nodes = NULL;

	if (infom->argc == 1)
	{
		nodes = infom->alias;
		while (nodes)
		{
			for_printing_alias(nodes);
			nodes = nodes->next;
		}
		return (0);
	}
	for (i = 1; infom->argv[i]; i++)
	{
		pp = for_strchr(infom->argv[i], '=');
		if (pp)
			for_set_alias(infom, infom->argv[i]);
		else
			for_printing_alias(for_node_starts_with(infom->alias, infom->argv[i], '='));
	}

	return (0);
}



