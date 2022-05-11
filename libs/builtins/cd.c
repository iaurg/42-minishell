#include "../../includes/builtins.h"

/*
[getcwd](https://man7.org/linux/man-pages/man3/getcwd.3.html): These functions return a null-terminated string containing an absolute pathname that is the current working directory of the calling process. The pathname is returned as the function result and via the argument buf, if present.

[chdir](https://man7.org/linux/man-pages/man2/chdir.2.html): changes the current working directory of the calling process to the directory specified in path

The relative path describes the directory you want to cd to in terms which are relative to your current directory. When you typed cd .., you were saying "go up one directory." The next directory up, from your login directory, was home.

To change directories using absolute pathnames, type cd /directory/directory; to change directories using relative pathnames, type cd directory to move one directory below, cd directory/directory to move two directories below, etc.; to jump from anywhere on the filesystem to your login directory, type cd;

/home/italo <- absolute path
.. <- relative path
home/italo <- relative path

Material:
https://ftp.kh.edu.tw/Linux/Redhat/en_6.2/doc/gsg/s1-navigating-cd.htm
https://www.geeksforgeeks.org/chdir-in-c-language-with-examples/
*/

char *get_cwd(void)
{
	char *cwd;

	cwd = NULL;
	if ((cwd = getcwd(NULL, 0)) == NULL)
		return (NULL);
	return (cwd);
}

// check if go up one directory
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

// cd ~ getenv("HOME")
int cd_home(char **envp)
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
int cd_dir(char **argv, char **envp)
{
	char *cwd;
	if (argv[1] == NULL)
		return (1);
	if ((cwd = get_cwd()) == NULL)
		return (1);
	if (ft_strncmp(argv[1], ".", 1) == 0)
		return (0);
	if ((tmp = ft_strjoin(cwd, "/")) == NULL)
		return (1);
	if ((tmp2 = ft_strjoin(tmp, argv[1])) == NULL)
		return (1);
}
*/

int	cd(char *argv[], t_list *envp[])
{
	int i;
	i = 0;
	if (!envp)
		return 0;
	if (ft_strncmp(argv[1], "~", 1) == 0 && cd_home(envp[0]) == 1)
		chdir(ms_getenv(envp, "HOME"));
	if (ft_strncmp(argv[1], "..", 2) == 0)
		chdir("..");
	else {
		chdir(argv[1]);
	}
	return (0);
}
