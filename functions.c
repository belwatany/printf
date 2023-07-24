#include "main.h"

/************************* PRINT CHARACTER *************************/

/**
 * print_char - Prints a character
 * @types: List of arguments
 * @buffer: The buffer array to handle print
 * @flags:  This calculates active flags
 * @width: The width
 * @precision: This is the precision specification
 * @size: A size specifier
 * Return: It returns the number of chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char ch = va_arg(types, int);

	return (handle_write_char(ch, buffer, flags, width, precision, size));
}
/************************* PRINT STRING *************************/
/**
 * print_string - This prints a string
 * @types: List of arguments
 * @buffer: The buffer array to handle print
 * @flags:  This calculates active flags
 * @width: Get width.
 * @precision: The precision specification
 * @size: A size specifier
 * Return: Returns number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int leng = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[leng] != '\0')
		leng++;

	if (precision >= 0 && precision < leng)
		leng = precision;

	if (width > leng)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], leng);
			for (i = width - leng; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - leng; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], leng);
			return (width);
		}
	}

	return (write(1, str, leng));
}
/************************* PRINT PERCENT SIGN %*************************/
/**
 * print_percent - This prints a percent sign
 * @types: List of arguments
 * @buffer: he buffer array to handle print
 * @flags:  This calculates active flags
 * @width: Get width.
 * @precision: The precision specification
 * @size: A size specifier
 * Return: Returns number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - This prints int
 * @types: List of arguments
 * @buffer: The buffer array to handle print
 * @flags:  This calculates the active flags
 * @width: Get width.
 * @precision: The precision specification
 * @size:A  size specifier
 * Return: Returns number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - This prints an unsigned number
 * @types:The list of arguments
 * @buffer:The buffer array to handle print
 * @flags:  This calculates active flags
 * @width: Get width.
 * @precision: The precision specification
 * @size: A size specifier
 * Return: Returns the numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
