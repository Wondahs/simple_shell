#include "main.h"

/**
 *_setenv - Sets @variable as an environment variable wih value @value
 *@variable: Variable to set.
 *@value: Value of @variable
 *
 *Return: 0 if success, -1 if fail.
 */
int _setenv(char *variable, char *value)
{
	int i = 0, j;
	char *new_var, **new_env, *temp;

	if (!variable || !value)
		return (-1);
	temp = malloc(_strlen(variable) + _strlen(value) + 2);
	new_var = _strdup(variable);
	temp = _strcpy(temp, new_var);
	free(new_var);
	new_var = temp;
	_strcat(new_var, "=");
	_strcat(new_var, value);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], variable, _strlen(variable)) == 0)
		{
			environ[i] = _strdup(new_var);
			free(new_var);
			return (0);
		}
	}
	new_env = (char **)malloc((i + 3) * sizeof(char *));
	for (j = 0; environ[j] != NULL; j++)
		new_env[j] = environ[j];
	new_env[j] = _strdup(new_var);
	new_env[j + 1] = NULL;
	free(new_var), free(environ);
	new_var = NULL;
	environ = new_env;
	return (0);
}

/**
 *_unsetenv - Unsets an environment variable
 *@variable: Variable to unset
 *
 *Return: 0 on success, -1 on fail.
 */
int _unsetenv(char *variable)
{
	int i = 0, size = 0, k = 0;
	char **temp;


	if (variable == NULL || !variable)
		return (-1);
	while (environ[size] != NULL)
		size++;
	temp = (char **)malloc((size + 1) * sizeof(char *));
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], variable, _strlen(variable)) != 0)
		{
			temp[k++] = environ[i];
		}
	}
	temp[k] = NULL;
	free(environ);
	environ = temp;
	return (0);
}

/**
 * copy_env - Copies environment variables.
 *
 *Return: Nothing.
 */
void copy_env(void)
{
	char **new_env;
	int size = 0, i;

	while (environ[size] != NULL)
		size++;
	new_env = (char **)malloc((size + 1) * (sizeof(char *)));
	for (i = 0; i < size; i++)
		new_env[i] = environ[i];
	new_env[i] = NULL;
	environ = new_env;
}

/**
 *free_cmd_t - Frees cmd_t struct
 *@cmmd: Struct to free
 *
 *Return: Nothing.
 */
void free_cmd_t(cmd_t *cmmd)
{
	int i;

	for (i = 0; i < cmmd->arg_count; i++)
	{
		free(cmmd->args[i]);
	}
	free(cmmd);
}
