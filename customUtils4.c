#include "main.h"

/**
 *count_slash - Counts number of forward slashes in an input string
 *@str: Input string
 *
 *This function is useful to check if a command was passed using
 *its absolute path, for example "/bin/ls" instead of "ls."
 *
 *Return: Number of forward slashes
 */
int count_slash(char *str)
{
	int i, len, slash = 0;

	len = _strlen(str);
	for (i = 0; i < len; i++)
	{
		if (str[i] == '/')
			slash++;
	}
	return (slash);
}

/**
 *abs_path - Checks if absolute path passed exists.
 *@str: Command passed.
 *
 *Return: Absolute path if it exists, and NULL if it does not
 */
char *abs_path(char *str)
{
	char *cmd;

	cmd = _strdup(str);
	if (cmd == NULL)
	{
		perror("abs_path");
		return (NULL);
	}
	if (access(cmd, X_OK) == 0)
		return (cmd);
	return (NULL);
}

/**
 *get_cmd - Extracts command if absolute path was passed.
 *@str: Absolute path of command.
 *
 *
 *Return: Command, or NULL if failed.
 */
char *get_cmd(char *str)
{
	int i, j = 0, slash_point = 0, len;
	char *cmd;

	len = _strlen(str);
	for (i = 0; i < len; i++)
	{
		if (str[i] == '/')
			slash_point = i;
	}
	cmd = malloc(len - slash_point);
	if (!cmd)
	{
		perror("get_cmd");
		return (NULL);
	}
	for (i = slash_point; i < len; i++)
		cmd[j++] = str[i];
	cmd[j] = '\0';
	return (cmd);
}

/**
 *_realloc - Used with _getline to reallocate memory when necessary.
 *@lineptr: Double pointer to array used to store line.
 *@n: Size of memory to allocate.
 *@tBytesRead: Total byted read into lineptr.
 *
 *Return: lineptr with specified memory on success, or NULL if failed
 */
char *_realloc(char **lineptr, int n, ssize_t tBytesRead)
{
	ssize_t i;
	char *temp;

	temp = (char *)malloc(n);
	if (!temp)
		return (NULL);
	for (i = 0; i < tBytesRead; i++)
		temp[i] = (*lineptr)[i];
	free(*lineptr);
	*lineptr = temp;
	return (*lineptr);
}
