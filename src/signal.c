/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:54:55 by itaureli          #+#    #+#             */
/*   Updated: 2022/06/01 19:58:05 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	*get_signal_triggered_status(void)
{
	static int	*triggered;

	if (!triggered)
	{
		triggered = (int *)malloc(sizeof(int));
		*triggered = 0;
	}
	return (triggered);
}

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
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_heredoc_signal(int signal_number)
{
	int	*triggered;

	triggered = get_signal_triggered_status();
	if (signal_number == SIGINT)
	{
		*triggered = 1;
		signal(SIGINT, handle_heredoc_signal);
	}
}
