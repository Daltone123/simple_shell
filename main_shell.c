#include "shell.h"

/**
 * hsh - main shell loop
 * @infom: the parameter & return info struct
 * @avv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *infom, char **avv)
{
	ssize_t r = 0;
	int builtin_rett = 0;

	while (r != -1 && builtin_rett != -2)
	{
		for_clearing_info(infom);
		if (for_interact(infom))
			for_puts("$ ");
		for_eputchar(BUF_FLUSH);
		r = for_get_input(infom);
		if (r != -1)
		{
			for_setting_info(infom, avv);
			builtin_rett = for_finding_builtin(infom);
			if (builtin_rett == -1)
				for_finding_cmd(infom);
		}
		else if (for_interact(infom))
			for_putchar('\n');
		for_free_info(infom, 0);
	}
	for_write_history(infom);
	for_free_info(infom, 1);
	if (!for_interact(infom) && infom->status)
		exit(infom->status);
	if (builtin_rett == -2)
	{
		if (infom->err_number == -1)
			exit(infom->status);
		exit(infom->err_number);
	}
	return (builtin_rett);
}

/**
 * for_finding_builtin - used to find a builtin command
 * @infom: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int for_finding_builtin(info_t *infom)
{
	int i, built_in_rett = -1;
	builtin_table builtintbl[] = {
		{"exit", for_myexit},
		{"env", for_myenvv},
		{"help", for_myhelp},
		{"history", for_myhistory},
		{"setenv", for_mysetenvv},
		{"unsetenv", for_myunsetenvv},
		{"cd", for_mycd},
		{"alias", for_myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (for_strcmp(infom->argv[0], builtintbl[i].type) == 0)
		{
			infom->forlinecount++;
			built_in_rett = builtintbl[i].func(infom);
			break;
		}
	return (built_in_rett);
}

/**
 * for_finding_cmd - used to find a command in PATH
 * @infom: the parameter & return info struct
 *
 * Return: void
 */
void for_finding_cmd(info_t *infom)
{
	char *paths = NULL;
	int i, k;

	infom->paths = infom->argv[0];
	if (infom->linecount_flags == 1)
	{
		infom->forlinecount++;
		infom->linecount_flags = 0;
	}
	for (i = 0, k = 0; infom->arg[i]; i++)
		if (!deliminator(infom->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	paths = for_finding_path(infom, for_getenvv(infom, "PATH="), infom->argv[0]);
	if (paths)
	{
		infom->paths = paths;
		for_fork_cmd(infom);
	}
	else
	{
		if ((for_interact(infom) || for_getenvv(infom, "PATH=")
					|| infom->argv[0][0] == '/') && is_cmd(infom, infom->argv[0]))
			for_fork_cmd(infom);
		else if (*(infom->arg) != '\n')
		{
			infom->status = 127;
			for_printing_error(infom, "not found\n");
		}
	}
}

/**
 * for_fork_cmd - forks a an exec thread to run cmd
 * @infom: the parameter & return info struct
 *
 * Return: void
 */
void for_fork_cmd(info_t *infom)
{
	pid_t child_pidd;

	child_pidd = fork();
	if (child_pidd == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pidd == 0)
	{
		if (execve(infom->paths, infom->argv, for_get_environs(infom)) == -1)
		{
			for_free_info(infom, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(infom->status));
		if (WIFEXITED(infom->status))
		{
			infom->status = WEXITSTATUS(infom->status);
			if (infom->status == 126)
				for_printing_error(infom, "Permission denied\n");
		}
	}
}


