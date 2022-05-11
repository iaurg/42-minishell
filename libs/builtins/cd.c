#include "../../includes/builtins.h"

char *get_cwd(void)
{
	char *cwd;

	cwd = NULL;
	if ((cwd = getcwd(NULL, 0)) == NULL)
		return (NULL);
	return (cwd);
}

int cd_up(char *cwd)
{
	char *tmp;

	tmp = NULL;
	if (cwd == NULL)
		return (1);
	if ((tmp = ft_strrchr(cwd, '/')) == NULL)
		return (1);
	if (tmp == cwd)
		return (1);
	*tmp = '\0';
	return (0);
}

int cd_home(t_list *envp[])
{
	char *home;

	home = NULL;
	if ((home = ms_getenv(envp, "HOME")) == NULL)
		return (1);
	if (chdir(home) == -1)
		return (1);
	return (0);
}

/*
Edge cases
If cd ./libs/libft -> . on first element calls wrong if
if cd /libs/ -> / on first element calls wrong if
Show error when wrong path
*/

static void print_cd_error(char *argv[])
{
		write(STDERR_FILENO, "bash: cd: ", 10);
		write(STDERR_FILENO, argv[1], ft_strlen(argv[1]));
		write(STDERR_FILENO, ": No such file or directory", 27);
		write(STDERR_FILENO, "\n", 1);
}

// TO-DO: refactor cd
// TO-DO: test more edge cases and bash comparisons
int	cd(char *argv[], t_list *envp[])
{
	if (!envp)
		return 0;
	if (argv[1] == NULL)
		return (0);
	if (chdir(argv[1]) < 0)
	{
		print_cd_error(argv);
		return (0);
	}
	if (ft_strncmp(argv[1], "~", 1) == 0 && cd_home(envp) == 1)
	{
		chdir(ms_getenv(envp, "HOME"));
		return (0);
	}
	if (ft_strncmp(argv[1], "..", 2) == 0)
	{
		chdir("..");
		return (0);
	}
	if (ft_strncmp(argv[1], ".", 1) == 0)
		return (0);
	if (ft_strncmp(argv[1], "/", 1) == 0 && chdir(argv[1]) == -1)
	{
		chdir("/");
		return (0);
	}
	chdir(argv[1]);
	return (0);
}
