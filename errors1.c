#include "shell.h"

/**
 * str_to_int - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       INT_MIN on error
 */
int str_to_int(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);

		i++;
	}

	return (result);
}

/**
 * print_error_message - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error_message(info_t *info, char *estr)
{
	printString(info->fname);
	printString(": ");
	print_decimalecimal(info->line_count, STDERR_FILENO);
	printString(": ");
	printString(info->argv[0]);
	printString(": ");
	printString(estr);
}

/**
 * print_decimalecimal - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimalecimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = printCharToStderr;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	i = 1000000000;
	while (i > 1)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
		i /= 10;
	}
	__putchar('0' + current);
	count++;

	return (count);
}


/**
 * int_to_base - Convert an integer to a string representation in
 * the given base
 * @num: The number to convert
 * @base: The base for the conversion
 * @flags: Argument flags
 *
 * Return: String representation of the number
 */
char *int_to_base(long int num, int base, int flags)
{
	static char buffer[50];
	char *ptr = &buffer[49];
	char *array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" :
	 "0123456789ABCDEF";
	char sign = 0;
	unsigned long n = (num < 0 && !(flags & CONVERT_UNSIGNED)) ? -num : num;

	*ptr = '\0';

	if (num < 0 && !(flags & CONVERT_UNSIGNED))
		sign = '-';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}


/**
 * remove_first_comment - Replace the first instance of '#' with '\0'
 * @buf: Address of the string to modify
 *
 * Return: Always 0
 */
void remove_first_comment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

