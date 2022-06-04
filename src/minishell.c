/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:07:33 by itaureli          #+#    #+#             */
/*   Updated: 2022/06/04 14:56:21 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	print_token_error(t_command *cmd, char c)
{
	write(STDERR_FILENO, "minishell: syntax error: `", 27);
	write(STDERR_FILENO, &c, 1);
	write(STDERR_FILENO, "` is not a valid token\n", 23);
	cmd->status = 127;
	return (1);
}

static int	using_prohibited_characters(char *buff, t_command *cmd)
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
		if (buff[i] == ';' || buff[i] == '\\' || buff[i] == '&')
			return (print_token_error(cmd, buff[i]));
	}
	return (0);
}

void	destroy_program(t_command *cmd)
{
	ft_lstclear(cmd->envp, free);
	free(cmd);
}

int	minishell(char *envp[])
{
	char		buffer[1024];
	int			status;
	t_command	*cmd;

	cmd = init_builtins(envp);
	signal(SIGQUIT, SIG_IGN);
	status = 1;
	while (status)
	{
		signal(SIGINT, signal_handler);
		if (take_input(buffer, cmd))
			break ;
		if (using_prohibited_characters(buffer, cmd) || read_input(buffer, cmd))
			continue ;
		status = handle_execute(cmd);
	}
	destroy_program(cmd);
	return (0);
}
