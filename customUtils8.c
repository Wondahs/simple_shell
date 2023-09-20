#include "main.h"

/**
 * cd - Change the current working directory.
 * @args: Pointer to the command arguments.
 * @argv_0: The name of the program.
 * @cmd_count: The command count.
 */
void cd(cmd_t *args, char *argv_0, int cmd_count)
{
	char *arg = args->args[1];
	char current_dir[1024];

	(void)cmd_count;
	(void)argv_0;
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		perror("cd");
		return;
	}
	if (arg == NULL || _strncmp(arg, "~", 1) == 0 ||
			_strncmp(arg, "$HOME", 5) == 0)
	{
		if (home(args) == -1)
			return;
	}
	else if (_strncmp(arg, "-", 1) == 0 || _strncmp(arg, "$OLDPWD", 7) == 0)
	{
		if (oldpwd(args) == -1)
			return;
	}
	else
	{
		int len = _strlen(arg);

		if (arg[len - 1] != '/')
		{
			arg[len++] = '/';
			arg[len] = '\0';
		}

		if (chdir(arg) == -1)
		{
			perror("cd");
			return;
		}
	}
	_setenv("OLDPWD", current_dir);
	_setenv("PWD", getcwd(NULL, 0));
}

/**
 * home - Handles home command for cd
 * @args: args
 *
 * Return: Nothing
 */
int home(cmd_t *args)
{
	const char *home = _getenv("HOME");
	int cd;

	cd = chdir(home);
	if (cd == -1)
	{
		perror("cd");
		args->foundPath = false;
		return (-1);
	}
	args->foundPath = true;
	return (0);
}

/**
 * oldpwd - Handles home command for cd
 * @args: args
 *
 * Return: Nothing
 */
int oldpwd(cmd_t *args)
{
	const char *oldpwd = _getenv("OLDPWD");
	int cd;

	cd = chdir(oldpwd);
	if (cd == -1)
	{
		perror("cd");
		args->foundPath = false;
		return (-1);
	}
	_printf("%s,\n", oldpwd);
	args->foundPath = true;
	return (0);
}


/**
 * cleanup - Frees necessary items
 * @cmmds: Cmmds
 * @args: Args
 *
 * Return: Nothing
 */
void cleanup(cmd_t *cmmds, cmd_t *args)
{
	if (args->foundPath == false)
	{
		free(cmmds), free(args), free(environ);
		exit(127);
	}
	free(cmmds), free(args), free(environ);
}
