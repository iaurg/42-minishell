/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 23:07:33 by itaureli          #+#    #+#             */
/*   Updated: 2022/02/06 21:19:14 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int	main(int argc, char *argv[])
{
	if (argc > 1 && argv)
	{
		print_error(MANY_ARGS);
		return (1);
	}
	char buffer[1024];
	int i;
	if (!argc && !argv)
		return (0);
	/*
	Print envps
	for(i = 0; envp[i] != (void *)0; i++)
	{
		printf("%s", envp[i]);
	}
	*/
	while (1)
	{
		if (take_input(buffer))
			continue;
		parse_input(buffer);
	}
	return (0);
}
