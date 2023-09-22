#include "main.h"

/**
 *expand - Handles variable expansion.
 *@args: Pointer to struct containing command information
 *
 *This command loops through each tokenized part of input command
 *and checks for "$". It currently handles "$$", "$?", and variable expansions
 *such as "$VARIABLE".
 *
 *Return: Nothing
 */
void expand(cmd_t *args)
{
	int i;

	for (i = 0; i < args->arg_count; i++)
	{
		if (args->args[i][0] == '$')
		{
			char *temp = NULL;

			if (args->args[i][1] == '?')
			{
				temp = args->args[i];
				args->args[i] = i_to_str(args->exit_status);
				free(temp);
				return;
			}
			else if (args->args[i][1] == '$')
			{
				pid_t pid = getpid();
				int pid_int = (int)pid;

				temp = args->args[i];
				args->args[i] = i_to_str(pid_int);
				free(temp);
				return;
			}
			else
			{
				expand_variable(args, i);
				return;
			}
		}
	}
}

#include <stdio.h>
#include <stdlib.h>

/**
 * i_to_str - Converts an integer to a string
 * @num: The integer to be converted
 *
 * Return: A dynamically allocated string representing the integer
 * orNULL is returned if memory allocation fails.
 */
char *i_to_str(int num)
{
	int num_digits = 0, index;
	int temp = num;
	char *str;

	while (temp != 0)
	{
		temp /= 10;
		num_digits++;
	}
	if (num == 0)
	{
		str = (char *)malloc(2);
		if (str)
		{
			str[0] = '0';
			str[1] = '\0';
		}
		return (str);
	}
	str = (char *)malloc(num_digits + 1);
	if (!str)
		return (NULL);
	index = num_digits - 1;
	while (num != 0)
	{
		int digit = num % 10;

		str[index--] = '0' + digit;
		num /= 10;
	}
	str[num_digits] = '\0';
	return (str);
}

/**
 *expand_variable - Carries out variable expansion
 *@args: Struct containing command info.
 *@i: Index
 *
 *Return: Nothing
 */
void expand_variable(cmd_t *args, int i)
{
	char *word = malloc(512);
	char *variable = NULL;
	char *temp = NULL;
	int k = 1, index = 0;

	while (args->args[i][k] != '\0')
	{
		word[index++] = args->args[i][k];
		k++;
	}
	word[index] = '\0';
	variable = _getenv(word);
	temp = args->args[i];
	args->args[i] = _strdup(variable);
	free(temp), free(word);
}
