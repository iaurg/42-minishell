/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:07:33 by itaureli          #+#    #+#             */
/*   Updated: 2022/04/16 19:12:00 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	buffer[1024];

	if (argc > 1 && argv)
	{
		print_error(NO_ARGS);
		return (1);
	}
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (take_input(buffer))
			break ;
		parse_input(buffer);
	}
	return (0);
}
