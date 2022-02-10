/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:07:33 by itaureli          #+#    #+#             */
/*   Updated: 2022/02/09 21:22:51 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int	main(int argc, char *argv[])
{
	if (argc > 1 && argv)
	{
		print_error(NO_ARGS);
		return (0);
	}
	if (!argc && !argv)
		return (1);
	char buffer[1024];
	int i;
	while (1)
	{
		if (take_input(buffer))
			continue;
		parse_input(buffer);
	}
	return (0);
}
