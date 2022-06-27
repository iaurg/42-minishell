/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:07:33 by itaureli          #+#    #+#             */
/*   Updated: 2022/06/26 22:25:13 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_strlen(buffer) == 0 || using_prohibited_characters(buffer, cmd)
			|| read_input(buffer, cmd))
			continue ;
		status = handle_execute(cmd);
		free_matrix(cmd->argv);
	}
	destroy_program(cmd);
	return (0);
}
