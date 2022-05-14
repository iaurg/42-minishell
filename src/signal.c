/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:54:55 by itaureli          #+#    #+#             */
/*   Updated: 2022/05/14 00:42:09 by vwildner         ###   ########.fr       */
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
		decoupled_shell_display();
		signal(SIGINT, signal_handler);
	}
}
