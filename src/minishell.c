/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:07:33 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/31 10:29:15 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO: must be improved to handle only prohibited characters outside of quotes
//static int	using_prohibited_characters(char *buff, t_command *cmd)
//{
//	int		i;
//	char	c;

//	i = -1;
//	if (buff == NULL)
//		return (1);
//	while (buff[++i] != '\0')
//	{
//		c = buff[i];
//		if (c == ';' || c == '\\' || c == '&')
//		{
//			write(STDERR_FILENO, "minishell: syntax error: `", 27);
//			write(STDERR_FILENO, &c, 1);
//			write(STDERR_FILENO, "` is not a valid token\n", 23);
//			cmd->status = 127;
//			return (1);
//		}
//	}
//	return (0);
//}

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
			break ;
		if (read_input(buffer, cmd))
			continue ;
		status = handle_execute(cmd);
	}
	return (0);
}
