/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:31:33 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/14 01:03:30 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	set_oldpwd(t_list *envp[], char *buf)
{
	char	*old_pwd;

	old_pwd = ft_strjoin("OLDPWD=", buf);
	export(old_pwd, envp);
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
	if (!envp || argv[1] == NULL)
		return 1;
	if (chdir(argv[1]) < 0)
	{
		print_cd_error(argv);
		return (1);
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
