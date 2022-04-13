/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:07:33 by itaureli          #+#    #+#             */
/*   Updated: 2022/04/13 08:38:11 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

static void	shell_prefix_handler(int signal)
{
	char cwd[1025];

	if (signal == SIGINT)
	{
		getcwd(cwd, 1024);
		ft_putstr_fd("\033[2D\033[0K", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_putstr_fd("\r\033[1;31muser@minishell\033[0;0m", STDERR_FILENO);
		ft_putstr_fd(":\033[1;34m", STDERR_FILENO);
		ft_putstr_fd(cwd, STDERR_FILENO);
		ft_putstr_fd("\033[0;0m$ ", STDERR_FILENO);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char buffer[1024];

	if (argc > 1 && argv)
	{
		print_error(NO_ARGS);
		return (1);
	}
	while (1)
	{
		signal(SIGINT, shell_prefix_handler);
		if (take_input(buffer))
			break;
		parse_input(buffer);
	}
	return (0);
}
