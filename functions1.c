#include "main.h"

/*************************THIS PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - This prints an unsigned number
 * @types: list a of arguments
 * @buffer: The buffer array to handle print
 * @flags:  This calculates active flags
 * @width: Get Width
 * @precision: The precision specification
 * @size: A size specifier
 * Return: Returns number of chars printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - This prints an unsigned number in octal notation
 * @types: list a of arguments
 * @buffer:The buffer array to handle print
 * @flags:  This calculates active flags
 * @width: Get Width
 * @precision: The precision specification
 * @size: A size specifier
 * Return: The number of chars printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL NOTATION **************/
/**
 * print_hexadecimal - This Prints an unsigned number in hexa notation
 * @types: list a of arguments
 * @buffer: The buffer array to handle print
 * @flags:  This calculates active flags
 * @width: Get width
 * @precision: the precision specification
 * @size: the size specifier
 * Return: The number of chars printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/****** PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL NOTATION **************/
/**
 * print_hexa_upper - This prints an unsigned number in upper hexa notation
 * @types: list a of arguments
 * @buffer: The buffer array to handle print
 * @flags:  This calculates active flags
 * @width: Get width
 * @precision: The precision specification
 * @size: The size specifier
 * Return:The number of chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/************** PRINT HEX NUMB IN LOWER OR UPPER **************/
/**
 * print_hexa - This prints a hexadecimal number in lower or upper
 * @types: list a of arguments
 * @map_to: An array of values to map the number to
 * @buffer: The buffer array to handle print
 * @flags:  This calculates active flags
 * @flag_ch: Also Calculates active flags
 * @width: Get Width
 * @precision: The precision specification
 * @size: A size specifier
 *
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

