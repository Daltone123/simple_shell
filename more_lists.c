#include "shell.h"

/**
 * list_length - determines length of linked list
 * @hh: pointer to first node
 *
 * Return: size of list
 */
size_t list_length(const list_t *hh)
{
	size_t i = 0;

	while (hh)
	{
		hh = hh->next;
		i++;
	}
	return (i);
}

/**
 * for_list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **for_list_to_strings(list_t *head)
{
	list_t *nodes = head;
	size_t i = list_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; nodes; nodes = nodes->next, i++)
	{
		str = malloc(for_strlength(nodes->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = for_strcpy(str, nodes->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * for_printing_list - prints all elements of a list_t linked list
 * @hh: pointer to first node
 *
 * Return: size of list
 */
size_t for_printing_list(const list_t *hh)
{
	size_t i = 0;

	while (hh)
	{
		for_puts(for_converting_number(hh->number, 10, 0));
		for_putchar(':');
		for_putchar(' ');
		for_puts(hh->str ? hh->str : "(nil)");
		for_puts("\n");
		hh = hh->next;
		i++;
	}
	return (i);
}

/**
 * for_node_starts_with - returns node whose string starts with prefix
 * @nodes: pointer to list head
 * @pref: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *for_node_starts_with(list_t *nodes, char *pref, char c)
{
	char *pp = NULL;

	while (nodes)
	{
		pp = for_starting_with(nodes->str, pref);
		if (pp && ((c == -1) || (*pp == c)))
			return (nodes);
		nodes = nodes->next;
	}
	return (NULL);
}

/**
 * for_get_node_index - gets the index of a node
 * @head: pointer to list head
 * @nodes: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t for_get_node_index(list_t *head, list_t *nodes)
{
	size_t i = 0;

	while (head)
	{
		if (head == nodes)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}


