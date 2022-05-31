/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:31:19 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/30 21:32:02 by vwildner         ###   ########.fr       */
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

static char	*get_inline_shell_display(t_list *envp[])
{
	char	cwd[1025];
	char	hostname[257];
	char	*tmp;
	char	*path;
	char	*tmp_user;

	getcwd(cwd, 1024);
	gethostname(hostname, 256);
	path = get_last_slash_arg(cwd);
	tmp = ft_strdup("\033[1;31m");
	tmp_user = ft_strdup(ms_getenv(envp, "USER"));
	tmp = ft_strjoin(tmp, tmp_user);
	tmp = ft_strjoin(tmp, "\033[0;36m@");
	tmp = ft_strjoin(tmp, hostname);
	tmp = ft_strjoin(tmp, " \033[0;34m");
	tmp = ft_strjoin(tmp, path);
	tmp = ft_strjoin(tmp, " ~ $\033[0m ");
	free(tmp_user);
	return (tmp);
}

static int	using_prohibited_characters(char *buff)
{
	int		i;
	char	c;

	i = -1;
	if (buff == NULL)
		return (1);
	while (buff[++i])
	{
		c = buff[i];
		if (c == ';' || c == '\\' || c == '&')
		{
			write(STDERR_FILENO, "minishell: syntax error: `", 27);
			write(STDERR_FILENO, &c, 1);
			write(STDERR_FILENO, "` is not a valid token\n", 23);
			return (1);
		}
	}
	return (0);
}

int	take_input(char *buffer, t_command *cmd)
{
	char	*tmp;
	char	*display;

	display = get_inline_shell_display(cmd->envp);
	tmp = readline(display);
	ft_strlcpy(buffer, tmp, ft_strlen(tmp) + 1);
	free(display);
	free(tmp);
	if (ft_strlen(tmp) > 0)
	{
		save_history(buffer);
		return (0);
	}
	if (using_prohibited_characters(buffer))
	{
		cmd->status = 127;
		return (0);
	}
	return (1);
}
