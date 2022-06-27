/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prohibited.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 22:23:31 by vwildner          #+#    #+#             */
/*   Updated: 2022/06/26 22:24:53 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_token_error(t_command *cmd, char c)
{
	write(STDERR_FILENO, "minishell: syntax error: `", 27);
	write(STDERR_FILENO, &c, 1);
	write(STDERR_FILENO, "` is not a valid token\n", 23);
	cmd->status = 127;
	return (1);
}

static int	check_redir(const char *buff)
{
	int	n_redir;

	n_redir = 0;
	while (buff[n_redir] == '>')
	{
		n_redir++;
		if (n_redir > 2)
			return (ft_putstr_fd(
					"minishell: syntax error near unexpected token `>\'\n",
					STDERR_FILENO), 1);
	}
	return (0);
}

static int	check_pipes(const char *buff)
{
	int		n_pipes;

	n_pipes = 0;
	while (buff[n_pipes] == '|')
	{
		n_pipes++;
		if (n_pipes > 1)
			return (ft_putstr_fd(
					"minishell: syntax error near unexpected token `|\'\n",
					STDERR_FILENO), 1);
	}
	return (0);
}

int	using_prohibited_characters(char *buff, t_command *cmd)
{
	int		i;

	i = -1;
	if (buff == NULL)
		return (1);
	while (buff[++i] != '\0')
	{
		if (buff[i] == '\'' && ft_strchr(&buff[i + 1], '\''))
			while (buff[++i] != '\'')
				;
		else if (buff[i] == '\"' && ft_strchr(&buff[i + 1], '\"'))
			while (buff[++i] != '\"')
				;
		if (check_redir(&buff[i]) || check_pipes(&buff[i]))
			return (1);
		if (buff[i] == ';' || buff[i] == '\\' || buff[i] == '&')
			return (print_token_error(cmd, buff[i]));
	}
	return (0);
}
