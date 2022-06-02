/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:31:19 by itaureli          #+#    #+#             */
/*   Updated: 2022/06/01 20:19:39 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	save_history(char *input)
{
	if (input && *input)
		add_history(input);
}

char	*get_last_slash_arg(char *arg)
{
	char	*args[256];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '/')
		{
			args[j] = &arg[i + 1];
			j++;
		}
		i++;
	}
	return (args[j - 1]);
}

//static char	*get_inline_shell_display(t_list *envp[])
//{
//	char	cwd[1025];
//	char	hostname[257];
//	char	*tmp;
//	char	*other;
//	char	*path;
//	char	*tmp_user;

//	getcwd(cwd, 1024);
//	gethostname(hostname, 256);
//	path = get_last_slash_arg(cwd);
//	tmp = ft_strdup("\033[1;31m");
//	tmp_user = ft_strdup(ms_getenv(envp, "USER"));
//	other = ft_strjoin(tmp, tmp_user);
//	free(tmp);
//	tmp = ft_strjoin(other, "\033[0;36m@");
//	free(other);
//	other = ft_strjoin(tmp, hostname);
//	free(tmp);
//	tmp = ft_strjoin(other, " \033[0;34m");
//	free(other);
//	other = ft_strjoin(tmp, path);
//	free(tmp);
//	tmp = ft_strjoin(other, " ~ $\033[0m ");
//	free(other);
//	free(tmp_user);
//	return (tmp);
//}

int	take_input(char *buffer, t_command *cmd)
{
	char	*tmp;

	(void)cmd;
	tmp = readline("[ minishell ]$ ");
	ft_strlcpy(buffer, tmp, ft_strlen(tmp) + 1);
	free(tmp);
	if (tmp == NULL)
		return (1);
	if (ft_strlen(buffer) == 0)
		return (0);
	if (ft_strlen(buffer) > 0)
	{
		save_history(buffer);
		return (0);
	}
	return (1);
}
