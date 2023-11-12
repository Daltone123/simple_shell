#include "shell.h"

/**
 * for_erratoi - used for converting a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int for_erratoi(char *s)
{
	int i = 0;
	unsigned long int output = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			output *= 10;
			output += (s[i] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (output);
}

/**
 * for_printing_error - used to print an error message
 * @infom: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void for_printing_error(info_t *infom, char *estr)
{
	for_eputs(infom->f_names);
	for_eputs(": ");
	for_printing_dd(infom->forlinecount, STDERR_FILENO);
	for_eputs(": ");
	for_eputs(infom->argv[0]);
	for_eputs(": ");
	for_eputs(estr);
}

/**
 * for_printing_dd - function prints a decimal (integer) number (base 10)
 * @inputt: the input
 * @fdd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int for_printing_dd(int inputt, int fdd)
{
	int (*__putchar)(char) = for_putchar;
	int i, count = 0;
	unsigned int _abs_, curr;

	if (fdd == STDERR_FILENO)
		__putchar = for_eputchar;
	if (inputt < 0)
	{
		_abs_ = -inputt;
		__putchar('-');
		count++;
	}
	else
		_abs_ = inputt;
	curr = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + curr / i);
			count++;
		}
		curr %= i;
	}
	__putchar('0' + curr);
	count++;

	return (count);
}

/**
 * for_converting_number - it is a converter function, a clone of itoa
 * @number: number
 * @bases: base
 * @flags: argument flags
 *
 * Return: string
 */
char *for_converting_number(long int number, int bases, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = number;

	if (!(flags & CONVERT_UNSIGNED) && number < 0)
	{
		n = -number;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % bases];
		n /= bases;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * for_removing_comments - a function is used to replace
 * first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void for_removing_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}


