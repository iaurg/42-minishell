/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:07:33 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/20 00:55:39 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	handle_quotes(t_command *cmd, int i)
{
	char	*tmp;

	tmp = NULL;
	if ((cmd->argv[i][0] == CHAR_DOUBLE_QT
		|| cmd->argv[i][0] == CHAR_SINGLE_QT))
	{
		tmp = ft_strtrim(cmd->argv[i], "\"\'");
		free(cmd->argv[i]);
		cmd->argv[i] = ft_strdup(tmp);
		free(tmp);
		return (1);
	}
	return (0);
}

void	handle_dollar_sign(t_command *cmd, char *tmp, int i)
{
	size_t	len;

	len = ft_strlen(cmd->argv[i]);
	if (cmd->argv[i][0] == '$')
	{
		if (handle_status(cmd, i))
			return ;
		tmp = ms_getenv(cmd->envp, &cmd->argv[i][1]);
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

void	expand_args(t_command *cmd)
{
	int		i;
	char	*tmp;
	size_t	len;

	i = -1;
	tmp = NULL;
	while (cmd->argv[++i])
	{
		if (handle_quotes(cmd, i))
			continue ;
		handle_dollar_sign(cmd, tmp, i);
		if (cmd->argv[i][0] == '~')
		{
			tmp = getenv("HOME");
			len = ft_strlen(cmd->argv[i]);
			free(cmd->argv[i]);
			if (len > 1)
				cmd->argv[i] = ft_strjoin(tmp, &cmd->argv[i][1]);
			else
				cmd->argv[i] = ft_strdup(tmp);
		}
	}
	cmd->argc = i;
}
