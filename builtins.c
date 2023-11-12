#include "shell.h"

/**
 * for_myexit - exits the shell
 * @infom: Structure that is containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int for_myexit(info_t *infom)
{
	int exit_check;

	if (infom->argv[1])
	{
		exit_check = for_erratoi(infom->argv[1]);
		if (exit_check == -1)
		{
			infom->status = 2;
			for_printing_error(infom, "Illegal number: ");
			for_eputs(infom->argv[1]);
			for_eputchar('\n');
			return (1);
		}
		infom->err_number = for_erratoi(infom->argv[1]);
		return (-2);
	}
	infom->err_number = -1;
	return (-2);
}

/**
 * for_mycd - use to change the current directory of the process
 * @infom: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int for_mycd(info_t *infom)
{
	char *s, *direction, buffer[1024];
	int chdir_rett;

	s = getcwd(buffer, 1024);
	if (!s)
		for_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!infom->argv[1])
	{
		direction = for_getenvv(infom, "HOME=");
		if (!direction)
			chdir_rett = /* TODO: what should this be? */
				chdir((direction = for_getenvv(infom, "PWD=")) ? direction : "/");
		else
			chdir_rett = chdir(direction);
	}
	else if (for_strcmp(infom->argv[1], "-") == 0)
	{
		if (!for_getenvv(infom, "OLDPWD="))
		{
			for_puts(s);
			for_putchar('\n');
			return (1);
		}
		for_puts(for_getenvv(infom, "OLDPWD=")), for_putchar('\n');
		chdir_rett =
			chdir((direction = for_getenvv(infom, "OLDPWD=")) ? direction : "/");
	}
	else
		chdir_rett = chdir(infom->argv[1]);
	if (chdir_rett == -1)
	{
		for_printing_error(infom, "can't cd to ");
		for_eputs(infom->argv[1]), for_eputchar('\n');
	}
	else
	{
		for_setenvv(infom, "OLDPWD", for_getenvv(infom, "PWD="));
		for_setenvv(infom, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * for_myhelp - use to change the current directory of the process
 * @infom: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int for_myhelp(info_t *infom)
{
	char **arg_array;

	arg_array = infom->argv;
	for_puts("help call works. Function not yet implemented \n");
	if (0)
		for_puts(*arg_array);
	return (0);
}


