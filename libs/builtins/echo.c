/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 04:54:03 by itaureli          #+#    #+#             */
/*   Updated: 2022/04/20 05:07:57 by itaureli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	echo(char **args)
{
	while (*args)
	{
		write(STDOUT_FILENO, *args, ft_strlen(*args));
		write(STDOUT_FILENO, " ", 1);
		args++;
	}
	return (0);
}

int	main(void)
{
	char *args[] = {
		"echo",
		"test",
		"test2",
		"test3",
		NULL
	};

	echo(args);
	return (0);
}
