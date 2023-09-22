#include "main.h"

/**
 * print_env - Prints environment variable.
 *
 */
void print_env(void)
{
	int i = 0;

	for (i = 0; environ[i] != NULL; i++)
		_printf("%s\n", environ[i]);
}
