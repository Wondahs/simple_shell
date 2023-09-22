#include "main.h"

/** This file contains the following functions:
 * checkPath
 * getPrompt
 * execute
 * tokenize_cmd
 */

/**
 *checkPath - Checks if given command can be executed before fork and execve.
 *@cmd: Pointer to command
 *
 *This function takes the command, and checks through the
 *environment variable PATH to check if the command can be executed.
 *
 *Return: Full path of command, or NULL if the command is not in PATH.
 */
char *checkPath(char *cmd)
{
	/* Get environment variable PATH*/
	char *envir = _getenv("PATH");
	char *token, *token_cpy, *full_path, *env_cpy = NULL;

	if (envir == NULL)
		return (NULL);
	/* Duplicate PATH*/
	env_cpy = _strdup(envir);

	/* Tokenize PATH */
	token = _strtok(env_cpy, ":");
	while (token != NULL)
	{
		/* Duplicate token and concatenate command to necessary PATHS*/
		token_cpy = malloc(_strlen(token) + _strlen(cmd) + 2);
		if (!token_cpy)
		{
			perror("malloc");
			return (NULL);
		}
		token_cpy = _strcpy(token_cpy, token);
		token_cpy = _strcat(token_cpy, "/");
		full_path = _strcat(token_cpy, cmd);
		/*printf("%s\n", full_path);*/
		if (access(full_path, X_OK) == 0)
		{
			free(env_cpy);
			env_cpy = NULL;
			return (full_path);
		}
		else
		{
			free(token_cpy);
			token_cpy = NULL;
			token = _strtok(NULL, ":");
		}
	}
	free(env_cpy);
	env_cpy = NULL;
	return (NULL);
}

/**
 *getPrompt - Prints '$' and receives command from user.
 *@cmmds: Struct containing command information
 *@args: Commands that have been split
 *
 *This function receives command, and copies it into a string
 *without including the '\n' character. If command is 'exit' it returns NULL.
 *
 *Return: Pointer to a copy of the command.
 */
char *getPrompt(cmd_t *cmmds, cmd_t *args)
{
	char *c_cpy;
	char *c = malloc(128);
	ssize_t i;
	int n = 20;
	buff_t buf;

	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "$ ", 2);
		fflush(stdout);
	}

	/* Get command */
	buf.index = 0;
	buf.count = 0;
	i = _getline(&c, &n, STDIN_FILENO, &buf);
	if (i == 0)
	{
		free(c), free(cmmds), free(args);
		exit(0);
	}
	if (i == 1)
	{
		free(c);
		return (NULL);
	}

	/* Set string terminator, duplicate command and return */
	if (c != NULL)
	{
		if (c[i - 1] == '\n')
			c[i - 1] = '\0';
		c[i] = '\0';
		c_cpy = _strdup(c);
		if (!c_cpy)
			perror("strdup error");
	}
	free(c);
	return (c_cpy);
}

/**
 *execute - Calls execve and runs the given command
 *@args: Pointer to struct containing commands info.
 *@cmmds: Pointer to struct containing commands info.
 *@cmd_count: Number of commands executed.
 *
 *Return: Nothing
 */
void execute(cmd_t *args, cmd_t *cmmds, int cmd_count)
{
	pid_t child_pid;
	int status;
	int i;

	child_pid = fork();
	if (child_pid == -1)
		perror("fork failed");
	if (child_pid == 0)
	{
		if (execve(args->args[0], args->args, environ) == -1)
			perror("execve");
	}
	else
	{
		wait(&status);
		if (WEXITSTATUS(status) != 0)
		{
			args->foundPath = false;
			if (cmmds->arg_count == cmd_count && args->piped)
			{
				free_cmd_t(args);
				free(cmmds), free(environ);
				exit(WEXITSTATUS(status));
			}
		}
		for (i = 0; args->args[i] != NULL; i++)
		{
			free(args->args[i]);
			args->args[i] = NULL;
		}
	}
}

/**
 *tokenize_cmd - Tokenizes command and checks for exit command
 *@cmd: Command
 *@args: An array into which command is split
 *@delim: Delimiter
 *
 *Return: Number of tokens of command, or -1 if command is "exit"
 */
int tokenize_cmd(char *cmd, char *args[], char *delim)
{
	int i = 0;
	char *token;

	token = _strtok(cmd, delim);
	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i++] = _strdup(token);
		token = _strtok(NULL, delim);
	}
	args[i] = NULL;
	return (i);
}
