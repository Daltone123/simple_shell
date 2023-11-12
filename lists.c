#include "shell.h"

/**
 * to_add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @number: node index used by history
 *
 * Return: size of list
 */
list_t *to_add_node(list_t **head, const char *str, int number)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	for_memset((void *)new_head, 0, sizeof(list_t));
	new_head->number = number;
	if (str)
	{
		new_head->str = for_strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * for_add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @number: node index used by history
 *
 * Return: size of list
 */
list_t *for_add_node_end(list_t **head, const char *str, int number)
{
	list_t *new_node, *nodes;

	if (!head)
		return (NULL);

	nodes = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->number = number;
	if (str)
	{
		new_node->str = for_strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (nodes)
	{
		while (nodes->next)
			nodes = node->next;
		nodes->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * for_printing_list_str - prints only the str element of a list_t linked list
 * @hh: pointer to first node
 *
 * Return: size of list
 */
size_t for_printing_list_str(const list_t *hh)
{
	size_t i = 0;

	while (hh)
	{
		for_puts(hh->str ? hh->str : "(nil)");
		for_puts("\n");
		hh = hh->next;
		i++;
	}
	return (i);
}

/**
 * for_delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @ind: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int for_delete_node_at_index(list_t **head, unsigned int ind)
{
	list_t *nodes, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!ind)
	{
		nodes = *head;
		*head = (*head)->next;
		free(nodes->str);
		free(nodes);
		return (1);
	}
	nodes = *head;
	while (nodes)
	{
		if (i == ind)
		{
			prev_node->next = nodes->next;
			free(nodes->str);
			free(nodes);
			return (1);
		}
		i++;
		prev_node = nodes;
		nodes = nodes->next;
	}
	return (0);
}

/**
 * to_free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void to_free_list(list_t **head_ptr)
{
	list_t *nodes, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (nodes)
	{
		next_node = nodes->next;
		free(nodes->str);
		free(nodes);
		nodes = next_node;
	}
	*head_ptr = NULL;
}


