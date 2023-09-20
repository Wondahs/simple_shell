#include "printf.h"

/**
 * _printf - Custom printf
 * @format: Input string
 *
 * This custom printf function only handles char, char * and int types.
 *
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
{
	va_list args;
	const char *p = format;
	int char_count = 0;

	va_start(args, format);
	condition(p, args, &char_count);
	va_end(args);
	return (char_count);
}
