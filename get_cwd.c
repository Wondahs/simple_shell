#include "main.h"


/**
 * get_cwd - A function to get the current working directory
 * Parameters: None
 *
 * Return: A pointer to a string containing the current working directory
 */
char *get_cwd()
{
	 char *cwd = malloc(1028);

	if (cwd == NULL)
	{
		perror("malloc");
		exit(1);
	}
	if (getcwd(cwd, 1028) == NULL)
	{
		perror("getcwd");
		free(cwd);
		exit(1);
	}
	return (cwd);
}

/**
 * change_dir - A function to change the current working directory
 * @dir: A pointer to a string containing the new directory to change to
 * Return: None
 */
void change_dir(char *dir)
{
	char *prev_dir = NULL;
	static char *cwd;

	if (dir == NULL || strcmp(dir, "~") == 0)
	{
		dir = getenv("HOME");
	}
	else if (strcmp(dir, "-") == 0)
	{
		if (prev_dir == NULL)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return;
		}
		dir = prev_dir;
	}
	cwd = get_cwd();

	if (chdir(dir) == -1)
	{
		perror("chdir");
	}
	else
	{
		setenv("PWD", dir, 1);
		free(prev_dir);
		prev_dir = cwd;
	}
}
/**
 *main -The function of the program
 * Parameters: The number of command-line arguments and an array
 * of pointers to the arguments.
 *
 *@argc: argument count
 *@argv: argument vector
 *Return: 0 on success or 1 with an error message
 */
int main(int argc, char **argv)
{
	if (argc > 2)
	{
		fprintf(stderr, "cd: too many arguments\n");
		return (1);
	}
	change_dir(argv[1]);
	return (0);
}
