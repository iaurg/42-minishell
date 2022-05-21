/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:31:19 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/21 20:23:00 by vwildner         ###   ########.fr       */
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
//	char	*path;
//	char	*tmp_user;

//	getcwd(cwd, 1024);
//	gethostname(hostname, 256);
//	path = get_last_slash_arg(cwd);
//	tmp = ft_strdup("\033[1;31m");
//	tmp_user = ft_strdup(ms_getenv(envp, "USER"));
//	tmp = ft_strjoin(tmp, tmp_user);
//	tmp = ft_strjoin(tmp, "\033[0;36m@");
//	tmp = ft_strjoin(tmp, hostname);
//	tmp = ft_strjoin(tmp, " \033[0;34m");
//	tmp = ft_strjoin(tmp, path);
//	tmp = ft_strjoin(tmp, " ~ $\033[0m ");
//	free(tmp_user);
//	return (tmp);
//}

int	take_input(char *input_text, t_command *cmd)
{
	char	*buffer;
	//char	*display;

	//display = get_inline_shell_display(cmd->envp);
	buffer = readline(">");
	//free(display);
	if (buffer)
	{
		save_history(buffer);
		ft_strlcpy(input_text, buffer, ft_strlen(buffer) + 1);
		return (0);
	}
	return (1);
}
