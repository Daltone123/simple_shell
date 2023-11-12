#include "shell.h"

/**
 * for_myenvv - used to print the current environment
 * @infom: is a Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int for_myenvv(info_t *infom)
{
	for_printing_list_str(infom->envv);
	return (0);
}

/**
 * for_getenvv - used to get the value of an environ variable
 * @infom: Structure containing potential arguments. Used to maintain
 * @names: envv variable name
 *
 * Return: the value
 */
char *for_getenvv(info_t *infom, const char *names)
{
	list_t *nodes = infom->envv;
	char *pp;

	while (nodes)
	{
		pp = for_starting_with(nodes->str, names);
		if (pp && *pp)
			return (pp);
		nodes = nodes->next;
	}
	return (NULL);
}

/**
 *for_mysetenvv - Initializes a new environment variable,
 *             or modify an existing one
 * @infom: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int for_mysetenvv(info_t *infom)
{
	if (infom->argc != 3)
	{
		for_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (for_setenvv(infom, infom->argv[1], infom->argv[2]))
		return (0);
	return (1);
}

/**
 * for_myunsetenvv - used to remove an environment variable
 * @infom: is a structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int for_myunsetenvv(info_t *infom)
{
	int i;

	if (infom->argc == 1)
	{
		for_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= infom->argc; i++)
		for_unsetenvv(infom, infom->argv[i]);

	return (0);
}

/**
 * for_populate_envv_list - populates envv linked list
 * @infom: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int for_populate_envv_list(info_t *infom)
{
	list_t *nodes = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		for_add_node_end(&nodes, environ[i], 0);
	infom->envv = nodes;
	return (0);
}


