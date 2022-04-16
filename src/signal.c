/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:54:55 by itaureli          #+#    #+#             */
/*   Updated: 2022/04/16 19:04:46 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(int signal_number)
{
	char	cwd[1025];

	printf("%d \n", signal_number);
	if (signal_number == SIGINT)
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
