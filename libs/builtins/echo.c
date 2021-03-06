/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 04:54:03 by itaureli          #+#    #+#             */
/*   Updated: 2022/06/07 18:17:43 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_flag_n(char *args)
{
	if (ft_strncmp(args, "-n", 2) == 0)
		return (1);
	return (0);
}

int	echo(char **args, int fd)
{
	int	i;
	int	has_n;

	i = 1;
	has_n = check_flag_n(args[i]);
	if (has_n)
		i++;
	while (args[i])
	{
		write(fd, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (has_n)
		return (0);
	write(fd, "\n", 1);
	return (0);
}
