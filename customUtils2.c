#include "main.h"

 /* This file contains the following functions:*/
 /* _getline*/
 /* _strcat*/
 /* _strtok*/
 /* _strcpy*/
 /* read_buffer*/

/**
 * _getline - Read a line from a file descriptor
 * and dynamically resize the buffer.
 * @lineptr: A pointer to a buffer where the line will be stored.
 * @n: A pointer to the size of the buffer.
 * @fd: The file descriptor from which to read the line.
 * @buf: Struct containing information about buffer.
 *
 * This function reads characters
 * from the given file descriptor until a newline
 * character is encountered or the end of the file is reached.
 * It dynamically resizes the buffer as needed to accommodate longer lines.
 * The line is stored in the 'lineptr'
 * buffer, and the 'n' pointer is updated with the new buffer size.
 * It needs to be used with read_buffer and _realloc functions.
 *
 * Return: The number of characters read, or -1 on error.
 */
ssize_t _getline(char **lineptr, int *n, int fd, buff_t *buf)
{
	char c;
	ssize_t tBytesRead = 0, bufferResult = 0;

	if (!lineptr || !n || !buf)
		return (-1);
	if (*lineptr == NULL || *n < 2)
	{
		*n = 64;
		*lineptr = (char *)malloc(*n);
		if (!(*lineptr))
			return (-1);
	}
	while (1)
	{

		if (tBytesRead >= (*n) - 2)
		{
			(*n) *= 2;
			*lineptr = _realloc(lineptr, *n, tBytesRead);
		}
		bufferResult = read_buffer(fd, buf);
		if (bufferResult < 0)
			return (-1);
		else if (bufferResult == 0 && tBytesRead == 0)
			return (0);
		else if (bufferResult == 0)
			break;
		c = buf->data[buf->index++];
		(*lineptr)[tBytesRead++] = c;
		if (c == '\n' && !(isatty(STDIN_FILENO) == 0))
			break;
	}
	(*lineptr)[tBytesRead] = '\0';
	return (tBytesRead);
}

/**
 * _strcat - Concatenates two strings.
 *
 * @dest: Destination string.
 * @src: Source string to concatenate.
 *
 * This function concatenates two strings.
 *
 * Return: Pointer to the concatenated string (dest).
 */
char *_strcat(char *dest, char *src)
{
	int i;
	size_t len;

	if (dest == NULL || src == NULL)
		return (NULL);

	len = _strlen(dest);

	for (i = 0; src[i] != '\0'; i++)
		dest[len++] = src[i];
	dest[len] = '\0';

	return (dest);
}

/**
 * _strtok - Tokenize a string based on specified delimiters.
 *
 * @str: The string to tokenize.
 * @delim:   A string containing the delimiter characters.
 *
 * This function tokenizes @str using the characters specified in
 * @delim as separators. It returns a pointer to the next token in the
 * string on each subsequent call, or NULL when there are no more tokens.
 *
 * Return: A pointer to the next token
 * or NULL if no more tokens are found.
 */
char *_strtok(char *str, char *delim)
{
	static char *next_token;
	char *token_start = NULL;
	bool found_delim = false;

	if (str != NULL)
		next_token = str;

	token_start = next_token;

	while (next_token && *next_token != '\0')
	{
		if (_strchr(delim, *next_token) != NULL)
		{
			*next_token = '\0';
			next_token++;
			found_delim = true;
			break;
		}
		next_token++;
	}

	if (found_delim || *token_start != '\0')
		return (token_start);
	else
		return (NULL);
}

/**
 * _strcpy - Copy a source string to a destination buffer.
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source string.
 *
 * Description:
 * This function copies the string pointed to by 'src' into the 'dest' buffer,
 * including the null-terminator. It ensures proper error handling for
 * invalid pointers and checks that the destination buffer has sufficient
 * space to hold the copied string.
 *
 * Return:
 * On success, it returns a pointer to 'dest'. If an error occurs due to
 * invalid pointers or insufficient destination buffer size, it returns NULL.
 */
char *_strcpy(char *dest, char *src)
{
	size_t i;
	size_t len;

	if (!src)
		return (NULL);

	len = _strlen(src);

	for (i = 0; i < len; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 *read_buffer - Used with _getline to store read data in a buffer.
 *@fd: File descriptor.
 *@buf: Struct containing buffer information.
 *
 *
 *Return: Number of bytes read.
 */
ssize_t read_buffer(int fd, buff_t *buf)
{
	if (buf->index >= buf->count)
	{
		buf->count = read(fd, buf->data, BUFFER_SIZE);
		if (buf->count <= 0)
			return (buf->count);
		buf->index = 0;
	}
	return (buf->count);
}
