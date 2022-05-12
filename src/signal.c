/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:54:55 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/12 06:10:48 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_signal_handler(int signal_number)
{
	if (signal_number == SIGINT)
	{
		write(1, "\n", 1);
		signal(SIGINT, child_signal_handler);
	}
}

void	signal_handler(int signal_number)
{
	if (signal_number == SIGINT)
	{
		write(1, "\n", 1);
		decopled_shell_display();
		signal(SIGINT, signal_handler);
	}
}
