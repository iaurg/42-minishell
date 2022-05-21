/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:07:33 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/21 20:22:44 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char		buffer[1024];
	int			status;
	t_command	*cmd;

	if (argc > 1 && argv)
	{
		print_error(NO_ARGS);
		return (1);
	}
	cmd = init_builtins(envp);
	atexit_clean(cmd);
	signal(SIGQUIT, SIG_IGN);
	status = 1;
	while (status)
	{
		signal(SIGINT, signal_handler);
		if (take_input(buffer, cmd))
			continue ;
		if (read_input(buffer, cmd))
			continue ;
		expand_args(cmd);
		status = execute(cmd);
	}
	ft_lstclear(cmd->envp, free);
	return (0);
}
