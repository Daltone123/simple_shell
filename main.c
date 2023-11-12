#include "shell.h"

/**
 * main - the entry point
 * @acc: arg count
 * @avv: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int acc, char **avv)
{
	info_t infom[] = { INFO_INIT };
	int fdd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fdd)
			: "r" (fdd));

	if (acc == 2)
	{
		fdd = open(avv[1], O_RDONLY);
		if (fdd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				for_eputs(avv[0]);
				for_eputs(": 0: Can't open ");
				for_eputs(avv[1]);
				for_eputchar('\n');
				for_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		infom->to_readfd = fdd;
	}
	for_populate_envv_list(infom);
	for_read_history(infom);
	hsh(infom, avv);
	return (EXIT_SUCCESS);
}


