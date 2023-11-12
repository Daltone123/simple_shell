#include "shell.h"

/**
 * for_memset - fills memory with a constant byte
 * @ss: the pointer to the memory area
 * @bb: the byte to fill *s with
 * @nn: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *for_memset(char *ss, char bb, unsigned int nn)
{
	unsigned int i;

	for (i = 0; i < nn; i++)
		ss[i] = bb;
	return (ss);
}

/**
 * for_free - frees a string of strings
 * @pp: string of strings
 */
void for_free(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * to_realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *to_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pp;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	pp = malloc(new_size);
	if (!pp)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		pp[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (pp);
}


