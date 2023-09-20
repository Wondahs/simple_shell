#include "main.h"

/* This contains the following code: */
/* _getenv */
/* _strlen */
/* _strncmp */
/* _strchr */
/* _strdup */

/**
 * _getenv - Get the value of an environment variable.
 * @name: The name of the environment variable to retrieve.
 *
 * This function searches for an environment variable by name and returns its
 * value as a string.
 *
 * Return: A pointer to the value of the environment variable,
 * or NULL if not found.
 */
char *_getenv(char *name)
{
	int i;

	if (name == NULL)
		return (NULL);
	for (i = 0; environ[i] != NULL; i++)
	{
		char *variable = environ[i];

		if (_strncmp(variable, name, _strlen(name)) == 0)
		{
			char *value = _strchr(variable, '=');

			if (value != NULL)
				return (value + 1);
		}
	}
	return (NULL);
}

/**
 * _strlen - Calculate the length of a string.
 * @c: The input string.
 *
 * This function calculates the length of the input string and returns it.
 *
 * Return: The length of the string.
 */
int _strlen(char *c)
{
	int len = 0;

	if (c == NULL)
		return (-1);
	while (c[len] != '\0')
		len++;
	return (len);
}

/**
 * _strncmp - Compare two strings up to a specified number of characters.
 * @s1: The first string.
 * @s2: The second string.
 * @n: The maximum number of characters to compare.
 *
 * This function compares two strings up to the specified number of characters
 * and returns 0 if they are equal, or 1 if they are not equal.
 *
 * Return: 0 if the strings are equal, 1 otherwise.
 */
int _strncmp(char *s1, char *s2, int n)
{
	int i;

	if ((s1 == NULL) || (s2 == NULL))
		return (-1);
	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
			return (1);
	}
	return (0);
}

/**
 * _strchr - Find the first occurrence of a character in a string.
 * @s: The input string.
 * @c: The character to search for.
 *
 * This function searches for the first occurrence of the specified character
 * in the input string and returns a pointer to that character,
 * or NULL if not found.
 *
 * Return: A pointer to the character, or NULL if not found.
 */
char *_strchr(char *s, char c)
{
	if ((s == NULL) || !c)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

/**
 *_strdup - Duplicates a string
 *@s: String to duplicate
 *
 *This function dynamically allocates memory for a new string
 *and duplicates the input string into the new string.
 *
 * Return: A pointer to the duplicate string on success,
 * NULL if it fails.
 */
char *_strdup(char *s)
{
	char *dup = NULL;
	int i;
	int len;

	if (s == NULL)
		return (NULL);
	len = _strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);

	for (i = 0; i < len; i++)
		dup[i] = s[i];
	dup[i] = '\0';
	return (dup);
}
