/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:07:33 by itaureli          #+#    #+#             */
/*   Updated: 2022/06/08 00:55:16 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_status(t_command *cmd, int i)
{
	if (cmd->argv[i][1] == '?'
		&& cmd->argv[i][2] == '\0')
	{
		free(cmd->argv[i]);
		cmd->argv[i] = ft_itoa(cmd->status);
		return (1);
	}
	return (0);
}

int	handle_quotes(t_command *cmd, char *arg, int i)
{
	char	*token;

	token = ft_strchr(cmd->argv[i], *arg);
	if (token != NULL)
	{
		while (token != NULL)
		{
			ft_memmove(token, token + 1, ft_strlen(token));
			token = ft_strchr(cmd->argv[i], *arg);
		}
		return (1);
	}
	return (0);
}

void	handle_dollar_sign(t_command *cmd, char *tmp, int i)
{
	size_t	len;
	char	*token;

	len = ft_strlen(cmd->argv[i]);
	token = ft_strchr(cmd->argv[i], '$');
	if (token != NULL)
	{
		if (handle_status(cmd, i))
			return ;
		tmp = ms_getenv(cmd->envp, ++token);
		if (tmp)
		{
			free(cmd->argv[i]);
			cmd->argv[i] = ft_strdup(tmp);
		}
		else if (len == 1)
			return ;
		else
		{
			free(cmd->argv[i]);
			cmd->argv[i] = ft_strdup("");
		}
	}
}

void	handle_home(t_command *cmd, char *tmp, int i)
{
	char	*sign_start;
	char	*tmp_arg;

	if (ft_strchr(cmd->argv[i], '~') != NULL)
	{
		tmp_arg = ft_strdup(cmd->argv[i]);
		sign_start = ft_strchr(tmp_arg, '~');
		tmp = ms_getenv(cmd->envp, "HOME");
		free(cmd->argv[i]);
		if (++sign_start != NULL)
			cmd->argv[i] = ft_strjoin(tmp, sign_start);
		else
			cmd->argv[i] = ft_strdup(tmp);
		free(tmp_arg);
	}
}

void	expand_args(t_command *cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (cmd->argv[++i])
	{
		if (cmd->s_quotes >= 2 && handle_quotes(cmd, "\'", i))
			continue ;
		if (cmd->d_quotes >= 2)
			handle_quotes(cmd, "\"", i);
		handle_dollar_sign(cmd, tmp, i);
		handle_home(cmd, tmp, i);
	}
	cmd->argc = i;
}
