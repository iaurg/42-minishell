/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:31:33 by itaureli          #+#    #+#             */
/*   Updated: 2022/06/27 22:19:51 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	set_oldpwd(t_list *envp[], char *buf)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = ft_strjoin("OLDPWD=", buf);
	export(old_pwd, envp);
	free(old_pwd);
	getcwd(buf, 1024);
	new_pwd = ft_strjoin("PWD=", buf);
	export(new_pwd, envp);
	free(new_pwd);
	return (0);
}

int	cd_home(t_list *envp[])
{
	char	*home;

	home = ms_getenv(envp, "HOME");
	if (home == NULL)
		return (1);
	if (chdir(home) == -1)
		return (1);
	return (0);
}

static void	print_cd_error(char *argv[])
{
	write(STDERR_FILENO, "minishell: cd: ", 10);
	write(STDERR_FILENO, argv[1], ft_strlen(argv[1]));
	write(STDERR_FILENO, ": No such file or directory", 27);
	write(STDERR_FILENO, "\n", 1);
}

int	cd(char *argv[], t_list *envp[])
{
	if (!envp || argv[1] == NULL)
		return (1);
	if (ft_strncmp(argv[1], "~", 2) == 0)
	{
		chdir(ms_getenv(envp, "HOME"));
		return (0);
	}
	if (chdir(argv[1]) < 0)
	{
		print_cd_error(argv);
		return (1);
	}
	return (0);
}
