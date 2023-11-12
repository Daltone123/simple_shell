#include "shell.h"

/**
 * for_clearing_info - used to initialize info_t struct
 * @infom: struct address
 */
void for_clearing_info(info_t *infom)
{
	infom->arg = NULL;
	infom->argv = NULL;
	infom->path = NULL;
	infom->argc = 0;
}

/**
 * for_setting_info - used to initialize info_t struct
 * @infom: struct address
 * @avv: argument vector
 */
void for_setting_info(info_t *infom, char **avv)
{
	int i = 0;

	infom->fname = av[0];
	if (infom->arg)
	{
		infom->argv = to_strtow(infom->arg, " \t");
		if (!infom->argv)
		{
			infom->argv = malloc(sizeof(char *) * 2);
			if (infom->argv)
			{
				infom->argv[0] = for_strdup(infom->arg);
				infom->argv[1] = NULL;
			}
		}
		for (i = 0; infom->argv && infom->argv[i]; i++)
			;
		infom->argc = i;

		for_replacing_alias(infom);
		for_replacing_vars(infom);
	}
}

/**
 * for_free_info - used to free info_t struct fields
 * @infom: struct address
 * @all: true if freeing all fields
 */
void for_free_info(info_t *infom, int all)
{
	for_free(infom->argv);
	infom->argv = NULL;
	infom->path = NULL;
	if (all)
	{
		if (!infom->cmd_buffer)
			free(infom->arg);
		if (infom->envv)
			to_free_list(&(infom->envv));
		if (infom->my_history)
			to_free_list(&(infom->my_history));
		if (infom->alias)
			to_free_list(&(infom->alias));
		for_free(infom->environ);
			infom->environ = NULL;
		be_free((void **)infom->cmd_buffer);
		if (infom->readfd > 2)
			close(info->to_readfd);
		for_putchar(BUF_FLUSH);
	}
}
