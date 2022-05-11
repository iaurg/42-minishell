/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:31:19 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/11 19:57:33 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	save_history(char *input)
{
	if (input && *input)
		add_history(input);
}

static char	*get_last_slash_arg(char *arg)
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
	char	*tmp;
	char	*other;
	char	*path;
	char	*tmp_user;

	getcwd(cwd, 1024);
	path = get_last_slash_arg(cwd);
	tmp_user = ft_strdup(ms_getenv(envp, "USER"));
	tmp = ft_strjoin(tmp_user, "\033[0;31m@minishell ");
	other = ft_strjoin(tmp, path);
	free(tmp_user);
	free(tmp);
	tmp = ft_strjoin(other, " ~ $\033[0m ");
	free(other);
	return (tmp);
}

int	take_input(char *input_text, t_command *cmd)
{
	char	*buffer;
	char	*display;

	display = get_inline_shell_display(cmd->envp);
	buffer = readline(display);
	free(display);
	if (buffer)
	{
		save_history(buffer);
		ft_strlcpy(input_text, buffer, ft_strlen(buffer) + 1);
		return (0);
	}
	return (1);
}
